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

PARSING_FAILED=0
PARS_LOGS_FILE="/tmp/push_swap_parsing_logs.txt"
PERF_INPUT_FILE="/tmp/push_swap_perf_input.txt"
STRUCTURED_LOGS_FILE="/tmp/push_swap_structured_logs.txt"
MOVES_100_FILE="/tmp/push_swap_moves_100.txt"
MOVES_500_FILE="/tmp/push_swap_moves_500.txt"
CONFIGS_100_FILE="/tmp/push_swap_configs_100.txt"
CONFIGS_500_FILE="/tmp/push_swap_configs_500.txt"

HAS_STRUCTURED_100=0
HAS_STRUCTURED_500=0

SPINNER_CHARS='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
SPINNER_IDX=0

main()
{
	echo ""
	reset_files
	run_parsing_tests
	PARSING_FAILED=$?
	generate_numbers 100 10
	run_perf_tests 100
	generate_numbers 500 10
	run_perf_tests 500
	echo ""
	print_results
	reset_files
}

reset_files()
{
	rm -rf ${PARS_LOGS_FILE}
	rm -rf ${PERF_INPUT_FILE}
	rm -rf ${STRUCTURED_LOGS_FILE}
	rm -rf ${MOVES_100_FILE}
	rm -rf ${MOVES_500_FILE}
	rm -rf ${CONFIGS_100_FILE}
	rm -rf ${CONFIGS_500_FILE}
	touch ${PARS_LOGS_FILE}
	touch ${MOVES_100_FILE}
	touch ${MOVES_500_FILE}
	touch ${CONFIGS_100_FILE}
	touch ${CONFIGS_500_FILE}
	touch ${STRUCTURED_LOGS_FILE}
}

get_spinner_char()
{
	local char="${SPINNER_CHARS:$SPINNER_IDX:1}"
	SPINNER_IDX=$(( (SPINNER_IDX + 1) % ${#SPINNER_CHARS} ))
	echo "$char"
}

update_progress_line()
{
	local label="$1"
	local current="$2"
	local total="$3"
	local percent=$((current * 100 / total))
	local spinner=$(get_spinner_char)
	
	# Pad percent to 3 characters
	local percent_str=$(printf "%3d" "$percent")
	
	if [ "$percent" -eq 100 ]; then
		echo -ne "\r${GREEN}✔ ${label} [${percent_str} %]${NC}\n"
	else
		echo -ne "\r${GREY}${spinner} ${label} [${percent_str} %]${NC}"
	fi
}

print_results()
{
	# Print structured logs if any
	if [ -s "${STRUCTURED_LOGS_FILE}" ]; then
		local log_count=$(grep -c "Best moves" "${STRUCTURED_LOGS_FILE}")
		local current_log=0
		
		while IFS= read -r line; do
			if echo "$line" | grep -q "Generating configs"; then
				current_log=$((current_log + 1))
				echo -e "${GREY}--- Push_swap logs [${current_log} / ${log_count}] ---${NC}"
				echo ""
			fi
			echo "$line"
		done < "${STRUCTURED_LOGS_FILE}"
		echo ""
	fi

	# Parsing logs
	if [ -s "${PARS_LOGS_FILE}" ]; then
		echo -e "${GREY}--- Parsing tests ---${NC}"
		echo ""
		cat "${PARS_LOGS_FILE}"
		echo ""
	fi

	# Perf results for 100
	print_perf_results 100 700 "${MOVES_100_FILE}" "${CONFIGS_100_FILE}" $HAS_STRUCTURED_100

	# Perf results for 500
	print_perf_results 500 5500 "${MOVES_500_FILE}" "${CONFIGS_500_FILE}" $HAS_STRUCTURED_500
}

print_perf_results()
{
	local count=$1
	local threshold=$2
	local moves_file=$3
	local configs_file=$4
	local has_structured=$5

	if [ ! -s "$moves_file" ]; then
		echo -e "${RED}✖ Perfs for ${count} random numbers => NO DATA${NC}\n"
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
		echo -e "${GREEN}✔ Perfs for ${count} random numbers => OK${NC}"
	else
		echo -e "${RED}✖ Perfs for ${count} random numbers => KO${NC}"
	fi

	# Print MIN, MOY, MAX
	echo -e "${BOLD_GREEN}-  ${GREY}MIN = ${BOLD_GREEN}${min}${NC}"
	echo -e "${BOLD_YELLOW}~  ${GREY}MOY = ${BOLD_YELLOW}${moy}${NC}"
	echo -e "${BOLD_RED}+  ${GREY}MAX = ${BOLD_RED}${max}${NC}"

	# Print configs if available
	if [ "$has_structured" -eq 1 ] && [ -s "$configs_file" ]; then
		echo -e "${GREY}🧠 Configs used:${NC}"
		sort "$configs_file" | uniq -c | while read -r cnt cfg; do
			echo -e "\t${BLUE}${cfg}${GREY} => ${NC}${cnt}"
		done
	fi
	echo ""
}

############# PERF TESTS #############

generate_numbers()
{
	input_len=$1
	input_count=$2
	for ((i=1; i<=input_count; i++)); do
		shuf --input-range=0-2147483647 -n ${input_len} | tr '\n' ' '
		echo
	done > "${PERF_INPUT_FILE}"
}

run_perf_tests()
{
	local size=$1
	local moves_file="/tmp/push_swap_moves_${size}.txt"
	local configs_file="/tmp/push_swap_configs_${size}.txt"
	local total=$(wc -l < "${PERF_INPUT_FILE}" | tr -d ' ')
	local current=0

	while IFS= read -r line; do
		current=$((current + 1))
		update_progress_line "Testing perfs (${size})..." "$current" "$total"
		
		# Run once and capture both stdout and stderr
		local tmp_stdout="/tmp/push_swap_stdout_$$.txt"
		local tmp_stderr="/tmp/push_swap_stderr_$$.txt"
		./push_swap $line > "$tmp_stdout" 2> "$tmp_stderr"
		
		stderr_output=$(cat "$tmp_stderr")
		stdout_output=$(cat "$tmp_stdout")
		
		# Check if stderr contains structured logs
		if echo "$stderr_output" | grep -q "Best moves"; then
			# Structured logs mode
			if [ "$size" -eq 100 ]; then
				HAS_STRUCTURED_100=1
			else
				HAS_STRUCTURED_500=1
			fi
			
			# Save structured logs
			echo "$stderr_output" >> "${STRUCTURED_LOGS_FILE}"
			
			# Extract best moves from stderr
			best_moves=$(echo "$stderr_output" | grep "Best moves" | grep -oE '[0-9]+' | tail -1)
			if [ -n "$best_moves" ]; then
				echo "$best_moves" >> "$moves_file"
			fi
			
			# Extract best config from stderr
			best_config=$(echo "$stderr_output" | grep "Best config" | sed 's/.*=> //')
			if [ -n "$best_config" ]; then
				echo "$best_config" >> "$configs_file"
			fi
		else
			# Raw moves mode - count lines from stdout
			if [ -n "$stdout_output" ]; then
				move_count=$(echo "$stdout_output" | wc -l | tr -d ' ')
				if [ "$move_count" -gt 0 ]; then
					echo "$move_count" >> "$moves_file"
				fi
			fi
		fi
		
		rm -f "$tmp_stdout" "$tmp_stderr"
	done < "${PERF_INPUT_FILE}"
}

############# PARSING TESTS #############

run_parsing_tests()
{
	local failed=0
	local total=17
	local current=0

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_do_nothing || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 2" "./push_swap 1 2 3 1" "                              -> duplicate      ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 3" "./push_swap \"\"" "                                   -> single empty   ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 4" "./push_swap 1 \"\" 3 4" "                             -> empty arg      ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 5" "./push_swap 1 + 3 4" "                              -> invalid '+'    ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 6" "./push_swap 1 - 3 4" "                              -> invalid '-'    ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 7" "./push_swap 1 2a3 4" "                              -> invalid '2a3'  ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 8" "./push_swap 1 2 -2147483649" "                      -> int underflow  ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error " 9" "./push_swap 1 2 2147483648" "                       -> int overflow   ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "10" "./push_swap 1 2 +2147483648" "                      -> int overflow   ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "11" "./push_swap 1 a2 3" "                               -> invalid start  ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_throw_error "12" "./push_swap \"\" \"\" \"\" \"\"" "                          -> all empty args ->   " "..." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "13" "./push_swap -2147483648 \"5 1\" +2147483647" "        -> space          ->   " "............." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "14" "./push_swap -2147483648 \" 5 1\" +2147483647" "       -> leading space  ->   " "............." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "15" "./push_swap -2147483648 \"5 1 \" +2147483647" "       -> trailing space ->   " "............." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
	test_should_work "16" "./push_swap -2147483648 \"   5   1   \" +2147483647" "-> multi spaces   ->   " "............." || failed=1

	current=$((current + 1))
	update_progress_line "Testing parsing...    " "$current" "$total"
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
