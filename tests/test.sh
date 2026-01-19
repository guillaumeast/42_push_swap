#!/bin/bash

BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
GRAY='\033[0;90m'
NC='\033[0m'
BOLD_GREEN='\033[1;32m'
BOLD_YELLOW='\033[1;33m'
BOLD_RED='\033[1;31m'
GREY='\033[0;90m'

# ============ CONFIGURATION ============
# Format: "count:iterations:threshold"
# count = number of random numbers per test
# iterations = how many tests to run
# threshold = max moves allowed for OK status
PERF_TESTS=(
	"100:100:700"
	"500:1000:5500"
)

# Worst case test file
WORST_500_FILE="tests/worst_500.txt"
WORST_500_THRESHOLD=5500

# Max number of push_swap logs to display per test series
MAX_LOGS_DISPLAY=10
# =======================================

PARSING_FAILED=0
PARS_LOGS_FILE="/tmp/push_swap_parsing_logs.txt"
PERF_INPUT_FILE="/tmp/push_swap_perf_input.txt"

SPINNER_CHARS='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
SPINNER_IDX=0

# Associative-like storage using files
declare -a PERF_MOVES_FILES=()
declare -a PERF_CONFIGS_FILES=()
declare -a PERF_HAS_STRUCTURED=()
declare -a PERF_ITERATIONS=()

reset_files()
{
	rm -f ${PARS_LOGS_FILE}
	rm -f ${PERF_INPUT_FILE}
	rm -f /tmp/push_swap_moves_*.txt
	rm -f /tmp/push_swap_configs_*.txt
	rm -f /tmp/push_swap_logs_*.txt
	rm -f /tmp/push_swap_stdout_*.txt
	rm -f /tmp/push_swap_stderr_*.txt
}

init_files()
{
	reset_files
	touch ${PARS_LOGS_FILE}
}

main()
{
	echo ""
	init_files
	run_parsing_tests
	PARSING_FAILED=$?
	
	# Run all configured perf tests
	for config in "${PERF_TESTS[@]}"; do
		IFS=':' read -r count iterations threshold <<< "$config"
		local moves_file="/tmp/push_swap_moves_${count}.txt"
		local configs_file="/tmp/push_swap_configs_${count}.txt"
		local logs_file="/tmp/push_swap_logs_${count}.txt"
		touch "$moves_file"
		touch "$configs_file"
		touch "$logs_file"
		PERF_MOVES_FILES+=("$moves_file")
		PERF_CONFIGS_FILES+=("$configs_file")
		PERF_HAS_STRUCTURED+=(0)
		PERF_ITERATIONS+=("$iterations")
		
		generate_numbers "$count" "$iterations"
		run_perf_tests "$count" "$iterations" "$((${#PERF_MOVES_FILES[@]} - 1))"
	done
	
	# Run worst case test
	if [ -f "$WORST_500_FILE" ]; then
		run_worst_case_test
	fi
	
	print_results
	reset_files
}

update_progress_line()
{
	local label="$1"
	local current="$2"
	local total="$3"
	local percent=$((current * 100 / total))
	local percent_str=$(printf "%3d" "$percent")
	
	# Get spinner char and increment index (inline to avoid subshell)
	local spinner="${SPINNER_CHARS:$SPINNER_IDX:1}"
	SPINNER_IDX=$(( (SPINNER_IDX + 1) % ${#SPINNER_CHARS} ))
	
	if [ "$percent" -eq 100 ]; then
		echo -ne "\r${GREEN}✔ ${label} [${percent_str} %]${NC}\n"
	else
		echo -ne "\r${BOLD_YELLOW}${spinner}${NC} ${GREY}${label} [${percent_str} %]${NC}"
	fi
}

print_results()
{
	# Print structured logs (only first MAX_LOGS_DISPLAY per series)
	local idx=0
	for config in "${PERF_TESTS[@]}"; do
		IFS=':' read -r count iterations threshold <<< "$config"
		local logs_file="/tmp/push_swap_logs_${count}.txt"
		
		if [ -f "$logs_file" ] && [ -s "$logs_file" ]; then
			cat "$logs_file"
			
			local hidden_count=$((iterations - MAX_LOGS_DISPLAY))
			if [ "$hidden_count" -gt 0 ]; then
				echo ""
				echo -e "${GREY}[... ${hidden_count} more iterations hidden]${NC}"
				echo ""
			fi
		fi
		idx=$((idx + 1))
	done
	
	# Worst case logs
	local worst_logs="/tmp/push_swap_logs_worst.txt"
	if [ -f "$worst_logs" ] && [ -s "$worst_logs" ]; then
		cat "$worst_logs"
		echo ""
	fi

	echo -e "${GREY}--- Results ---${NC}"
	
	# Parsing logs
	if [ -s "${PARS_LOGS_FILE}" ]; then
		echo ""
		cat "${PARS_LOGS_FILE}"
		echo ""
	fi

	# Perf results for each configured test
	local idx=0
	for config in "${PERF_TESTS[@]}"; do
		IFS=':' read -r count iterations threshold <<< "$config"
		print_perf_results "$count" "$iterations" "$threshold" "${PERF_MOVES_FILES[$idx]}" "${PERF_CONFIGS_FILES[$idx]}" "${PERF_HAS_STRUCTURED[$idx]}"
		idx=$((idx + 1))
	done
	
	# Worst case results
	if [ -f "/tmp/push_swap_moves_worst.txt" ] && [ -s "/tmp/push_swap_moves_worst.txt" ]; then
		print_perf_results "500 worst" "1" "$WORST_500_THRESHOLD" "/tmp/push_swap_moves_worst.txt" "/tmp/push_swap_configs_worst.txt" "1"
	fi
}

print_perf_results()
{
	local count=$1
	local iterations=$2
	local threshold=$3
	local moves_file=$4
	local configs_file=$5
	local has_structured=$6

	if [ ! -s "$moves_file" ]; then
		echo -e "${RED}✖ Perfs for ${count} random numbers (${iterations} iterations) => NO DATA${NC}\n"
		return
	fi

	# Calculate MIN, MOY, MAX using awk for reliability
	local stats=$(awk '
		BEGIN { min = 999999999; max = 0; sum = 0; count = 0 }
		{
			val = $1 + 0
			if (val < min) min = val
			if (val > max) max = val
			sum += val
			count++
		}
		END {
			if (count > 0) {
				printf "%d %d %d", min, int(sum/count), max
			} else {
				printf "0 0 0"
			}
		}
	' "$moves_file")
	
	local min=$(echo "$stats" | cut -d' ' -f1)
	local moy=$(echo "$stats" | cut -d' ' -f2)
	local max=$(echo "$stats" | cut -d' ' -f3)

	# Print OK/KO based on threshold
	if [ "$max" -le "$threshold" ]; then
		echo -e "${GREEN}✔ Perfs for ${count} random numbers (${iterations} iterations) => OK${NC}"
	else
		echo -e "${RED}✖ Perfs for ${count} random numbers (${iterations} iterations) => KO${NC}"
	fi

	# Print MIN, MOY, MAX
	echo -e "${BOLD_GREEN}-  ${GREY}MIN = ${BOLD_GREEN}${min}${NC}"
	echo -e "${BOLD_YELLOW}~  ${GREY}MOY = ${BOLD_YELLOW}${moy}${NC}"
	echo -e "${BOLD_RED}+  ${GREY}MAX = ${BOLD_RED}${max}${NC}"

	# Print configs if available
	if [ "$has_structured" -eq 1 ] && [ -s "$configs_file" ]; then
		echo -e "${GREY}🧠 Configs used:${NC}"
		sort "$configs_file" | uniq -c | sort -n | while read -r cnt cfg; do
			echo -e "\t${BLUE}${cfg}${GREY} => ${NC}${cnt}"
		done
	fi
	echo ""
}

############# PERF TESTS #############

generate_numbers()
{
	local input_len=$1
	local input_count=$2
	
	# Clear the file first
	> "${PERF_INPUT_FILE}"
	
	for ((i=1; i<=input_count; i++)); do
		# Update spinner during generation (shows 0% but spinner animates)
		update_progress_line "Testing perfs (${input_len})..." "0" "1"
		shuf --input-range=0-2147483647 -n ${input_len} | tr '\n' ' ' >> "${PERF_INPUT_FILE}"
		echo >> "${PERF_INPUT_FILE}"
	done
}

run_perf_tests()
{
	local size=$1
	local iterations=$2
	local idx=$3
	local moves_file="/tmp/push_swap_moves_${size}.txt"
	local configs_file="/tmp/push_swap_configs_${size}.txt"
	local logs_file="/tmp/push_swap_logs_${size}.txt"
	local total=$(wc -l < "${PERF_INPUT_FILE}" | tr -d ' ')
	local current=0

	while IFS= read -r line; do
		current=$((current + 1))
		update_progress_line "Testing perfs (${size})..." "$current" "$total"
		
		local tmp_stdout="/tmp/push_swap_stdout_$$.txt"
		local tmp_stderr="/tmp/push_swap_stderr_$$.txt"
		./push_swap $line > "$tmp_stdout" 2> "$tmp_stderr"
		
		local stderr_output=$(cat "$tmp_stderr")
		local stdout_output=$(cat "$tmp_stdout")
		
		local best_moves_line=""
		if echo "$stderr_output" | grep -q "Best moves"; then
			best_moves_line=$(echo "$stderr_output" | grep "Best moves")
		elif echo "$stdout_output" | grep -q "Best moves"; then
			best_moves_line=$(echo "$stdout_output" | grep "Best moves")
		fi
		
		if [ -n "$best_moves_line" ]; then
			PERF_HAS_STRUCTURED[$idx]=1
			
			# Only save logs for first MAX_LOGS_DISPLAY iterations
			if [ "$current" -le "$MAX_LOGS_DISPLAY" ]; then
				echo "" >> "$logs_file"
				echo -e "${GREY}--- Push_swap logs [${size} => ${current} / ${iterations}] ---${NC}" >> "$logs_file"
				echo "$stderr_output" >> "$logs_file"
			fi
			
			local clean_line=$(echo "$best_moves_line" | sed 's/\x1b\[[0-9;]*m//g')
			local best_moves=$(echo "$clean_line" | sed 's/.*=> *//' | tr -d ' ')
			if [ -n "$best_moves" ]; then
				echo "$best_moves" >> "$moves_file"
			fi
			
			local best_config=$(echo "$stderr_output" | grep "Best config" | sed 's/\x1b\[[0-9;]*m//g' | sed 's/.*=> *//' | tr -d '\n')
			if [ -n "$best_config" ]; then
				echo "$best_config" >> "$configs_file"
			fi
		else
			if [ -s "$tmp_stdout" ]; then
				local move_count=$(wc -l < "$tmp_stdout" | tr -d ' ')
				if [ "$move_count" -gt 0 ]; then
					echo "$move_count" >> "$moves_file"
				fi
			fi
		fi
		
		rm -f "$tmp_stdout" "$tmp_stderr"
	done < "${PERF_INPUT_FILE}"
}

run_worst_case_test()
{
	local moves_file="/tmp/push_swap_moves_worst.txt"
	local configs_file="/tmp/push_swap_configs_worst.txt"
	local logs_file="/tmp/push_swap_logs_worst.txt"
	
	touch "$moves_file"
	touch "$configs_file"
	touch "$logs_file"
	
	update_progress_line "Testing perfs (worst)." "0" "1"
	
	# Read the worst case input
	local line=$(cat "$WORST_500_FILE" | tr '\n' ' ')
	
	local tmp_stdout="/tmp/push_swap_stdout_$$.txt"
	local tmp_stderr="/tmp/push_swap_stderr_$$.txt"
	./push_swap $line > "$tmp_stdout" 2> "$tmp_stderr"
	
	local stderr_output=$(cat "$tmp_stderr")
	local stdout_output=$(cat "$tmp_stdout")
	
	local best_moves_line=""
	if echo "$stderr_output" | grep -q "Best moves"; then
		best_moves_line=$(echo "$stderr_output" | grep "Best moves")
	elif echo "$stdout_output" | grep -q "Best moves"; then
		best_moves_line=$(echo "$stdout_output" | grep "Best moves")
	fi
	
	if [ -n "$best_moves_line" ]; then
		echo "" >> "$logs_file"
		echo -e "${GREY}--- Push_swap logs [worst 500] ---${NC}" >> "$logs_file"
		echo "$stderr_output" >> "$logs_file"
		
		local clean_line=$(echo "$best_moves_line" | sed 's/\x1b\[[0-9;]*m//g')
		local best_moves=$(echo "$clean_line" | sed 's/.*=> *//' | tr -d ' ')
		if [ -n "$best_moves" ]; then
			echo "$best_moves" >> "$moves_file"
		fi
		
		local best_config=$(echo "$stderr_output" | grep "Best config" | sed 's/\x1b\[[0-9;]*m//g' | sed 's/.*=> *//' | tr -d '\n')
		if [ -n "$best_config" ]; then
			echo "$best_config" >> "$configs_file"
		fi
	else
		if [ -s "$tmp_stdout" ]; then
			local move_count=$(wc -l < "$tmp_stdout" | tr -d ' ')
			if [ "$move_count" -gt 0 ]; then
				echo "$move_count" >> "$moves_file"
			fi
		fi
	fi
	
	rm -f "$tmp_stdout" "$tmp_stderr"
	
	update_progress_line "Testing perfs (worst)." "1" "1"
}

############# PARSING TESTS #############

run_parsing_tests()
{
	local failed=0
	local total=17
	local current=0

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_do_nothing || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 2" "./push_swap 1 2 3 1" "                              -> duplicate      ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 3" "./push_swap \"\"" "                                   -> single empty   ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 4" "./push_swap 1 \"\" 3 4" "                             -> empty arg      ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 5" "./push_swap 1 + 3 4" "                              -> invalid '+'    ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 6" "./push_swap 1 - 3 4" "                              -> invalid '-'    ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 7" "./push_swap 1 2a3 4" "                              -> invalid '2a3'  ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 8" "./push_swap 1 2 -2147483649" "                      -> int underflow  ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 9" "./push_swap 1 2 2147483648" "                       -> int overflow   ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "10" "./push_swap 1 2 +2147483648" "                      -> int overflow   ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "11" "./push_swap 1 a2 3" "                               -> invalid start  ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "12" "./push_swap \"\" \"\" \"\" \"\"" "                          -> all empty args ->   " "..." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "13" "./push_swap -2147483648 \"5 1\" +2147483647" "        -> space          ->   " "............." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "14" "./push_swap -2147483648 \" 5 1\" +2147483647" "       -> leading space  ->   " "............." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "15" "./push_swap -2147483648 \"5 1 \" +2147483647" "       -> trailing space ->   " "............." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "16" "./push_swap -2147483648 \"   5   1   \" +2147483647" "-> multi spaces   ->   " "............." || failed=1

	current=$((current + 1)); update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "17" "./push_swap 0 000000000000000000000000000000001 2" "-> long but int   ->   " "............." || failed=1

	return $failed
}

test_should_do_nothing()
{
	stdout=$(./push_swap 2>/dev/null)
	stderr=$(./push_swap 2>&1 >/dev/null)
	ret=$?
	
	if [ -z "$stdout" ] && [ -z "$stderr" ] && [ $ret -eq 0 ]; then
		echo -e "Test  1: ${BLUE}./push_swap${NC}                                       -> no arg         ->    should print nothing and return 0 ${GRAY}...............${NC} ${GREEN}✔${NC}" >> "${PARS_LOGS_FILE}"
		return 0
	else
		echo -e "Test  1: ${BLUE}./push_swap${NC}                                       -> no arg         ->    should print nothing and return 0 ${GRAY}...............${NC} ${RED}✖${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stdout: '$stdout'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stderr: '$stderr'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Return code: $ret${NC}" >> "${PARS_LOGS_FILE}"
		return 1
	fi
}

test_should_throw_error()
{
	local test_num="$1"
	local command="$2"
	local description="$3"
	local dots="$4"
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if echo "$stderr" | grep -q "Error" && [ $ret -ne 0 ]; then
		echo -e "Test ${test_num}: ${BLUE}${command}${NC} ${description} should print 'Error' to stderr and return > 0 ${GRAY}${dots}${NC} ${GREEN}✔${NC}" >> "${PARS_LOGS_FILE}"
		return 0
	else
		echo -e "Test ${test_num}: ${BLUE}${command}${NC} ${description} should print 'Error' to stderr and return > 0 ${GRAY}${dots}${NC} ${RED}✖${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stdout: '$stdout'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stderr: '$stderr'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Return code: $ret${NC}" >> "${PARS_LOGS_FILE}"
		return 1
	fi
}

test_should_work()
{
	local test_num="$1"
	local command="$2"
	local description="$3"
	local dots="$4"
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if [ -n "$stdout" ] && [ $ret -eq 0 ]; then
		echo -e "Test ${test_num}: ${BLUE}${command}${NC} ${description} should print to stdout and return 0 ${GRAY}${dots}${NC} ${GREEN}✔${NC}" >> "${PARS_LOGS_FILE}"
		return 0
	else
		echo -e "Test ${test_num}: ${BLUE}${command}${NC} ${description} should print to stdout and return 0 ${GRAY}${dots}${NC} ${RED}✖${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stdout: '$stdout'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Stderr: '$stderr'${NC}" >> "${PARS_LOGS_FILE}"
		echo -e "    ${RED}Return code: $ret${NC}" >> "${PARS_LOGS_FILE}"
		return 1
	fi
}

############# EXEC #############
main
############# EXEC #############