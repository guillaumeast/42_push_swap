#!/bin/bash

PUSH_SWAP="./push_swap"
CHECKER="./checker"

BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
GRAY='\033[0;90m'
NC='\033[0m'
GREY='\033[0;90m'

COL1_WIDTH=49
COL2_WIDTH=26

STDOUT_GOT=$(mktemp)
STDERR_GOT=$(mktemp)
STDOUT_EXP=$(mktemp)
STDERR_EXP=$(mktemp)

cleanup()
{
	rm -f "$STDOUT_GOT" "$STDERR_GOT" "$STDOUT_EXP" "$STDERR_EXP"
}

trap cleanup EXIT

main()
{
	check_program_exists "$PUSH_SWAP" 1
	run_parsing_tests "$PUSH_SWAP"
	
	check_program_exists "$CHECKER" 0
	checker_exists=$?
	if [ $checker_exists -eq 0 ]; then
		run_parsing_tests "$CHECKER"
		run_checker_instruction_tests
		run_checker_validation_tests
		run_combined_random_tests
	fi
}

check_program_exists()
{
	local program="$1"
	local required="$2"
	
	if [ ! -f "$program" ]; then
		if [ "$required" -eq 1 ]; then
			echo -e "${RED}✖ Error: $program not found in current directory${NC}"
			exit 1
		else
			echo -e "${YELLOW}⚠ Warning: $program not found, skipping checker tests${NC}"
			return 1
		fi
	fi
	
	if [ ! -x "$program" ]; then
		if [ "$required" -eq 1 ]; then
			echo -e "${RED}✖ Error: $program is not executable${NC}"
			exit 1
		else
			echo -e "${YELLOW}⚠ Warning: $program is not executable, skipping checker tests${NC}"
			return 1
		fi
	fi
	
	return 0
}

############# PARSING TESTS #############

run_parsing_tests()
{
	local program="$1"
	local failed=0

	echo ""
	echo -e "${GREY}--- $program parsing tests ---${NC}\n"
	test_should_do_nothing "$program" " 1" || failed=1
	test_should_throw_error "$program" " 2" "\"\"" "single empty" || failed=1
	test_should_throw_error "$program" " 3" "\"\" \"\" \"\" \"\"" "all empty args" || failed=1
	test_should_throw_error "$program" " 4" "1 2 3 1" "duplicate" || failed=1
	test_should_throw_error "$program" " 5" "1 \"\" 3 4" "empty arg" || failed=1
	test_should_throw_error "$program" " 6" "1 + 3 4" "invalid '+'" || failed=1
	test_should_throw_error "$program" " 7" "1 - 3 4" "invalid '-'" || failed=1
	test_should_throw_error "$program" " 8" "1 2a 4" "invalid '2a'" || failed=1
	test_should_throw_error "$program" " 9" "1 a2 3" "invalid 'a2'" || failed=1
	test_should_throw_error "$program" "10" "1 2 -2147483649" "int underflow" || failed=1
	test_should_throw_error "$program" "11" "1 2 2147483648" "int overflow" || failed=1
	test_should_throw_error "$program" "12" "1 2 +2147483648" "int overflow with sign" || failed=1
	test_should_work "$program" "13" "-2147483648 \"5 1\" +2147483647" "space" || failed=1
	test_should_work "$program" "14" "-2147483648 \" 5 1\" +2147483647" "leading space" || failed=1
	test_should_work "$program" "15" "-2147483648 \"5 1 \" +2147483647" "trailing space" || failed=1
	test_should_work "$program" "16" "-2147483648 \"   5   1   \" +2147483647" "multi spaces" || failed=1
	test_should_work "$program" "17" "2 000000000000000000000000000000001 0" "long but int" || failed=1

	return $failed
}

############# CHECKER INSTRUCTION TESTS #############

run_checker_instruction_tests()
{
	local failed=0

	echo ""
	echo -e "${GREY}--- $CHECKER instruction tests ---${NC}\n"
	test_checker_invalid_instruction " 1" "2 1 3 0" $'\nsa\nrra\n' '\nsa\nrra\n' "first line empty" || failed=1
	test_checker_invalid_instruction " 2" "2 1 3 0" $'sa\nrra\n\n' 'sa\nrra\n\n' "last line empty" || failed=1
	test_checker_invalid_instruction " 3" "2 1 3 0" $'sa\n\nrra\n' 'sa\n\nrra\n' "middle line empty" || failed=1
	test_checker_invalid_instruction " 4" "2 1 3 0" 'sarra' 'sarra' "no newline" || failed=1
	test_checker_invalid_instruction " 5" "2 1 3 0" $'sarra\n' 'sarra\n' "first newline missing" || failed=1
	test_checker_invalid_instruction " 6" "2 1 3 0" $'sa\nrra' 'sa\nrra' "last newline missing" || failed=1
	test_checker_invalid_instruction " 7" "2 1 3 0" $'saa\nrra\n' 'saa\nrra\n' "invalid instruction" || failed=1
	test_checker_invalid_instruction " 8" "2 1 3 0" $'sa \nrra\n' 'sa \nrra\n' "space in instruction" || failed=1
	test_checker_invalid_instruction " 9" "2 1 3 0" $'pp\nrra\n' 'pp\nrra\n' "unknown instruction" || failed=1
	test_checker_invalid_instruction "10" "2 1 3 0" $' sa\nrra\n' ' sa\nrra\n' "space before" || failed=1
	test_checker_invalid_instruction "11" "2 1 3 0" $'sa\nrra\n ' 'sa\nrra\n ' "space after" || failed=1

	return $failed
}

############# CHECKER VALIDATION TESTS #############

run_checker_validation_tests()
{
	local failed=0

	echo ""
	echo -e "${GREY}--- $CHECKER validation tests ---${NC}\n"
	test_checker_should_print_ok " 1" "3 1 0 2" $'pb\nsa\npa\nra\n' 'pb\nsa\npa\nra\n' "correct sort" || failed=1
	test_checker_should_print_ok " 2" "3 1 0 2" $'ra\nsa\n' 'ra\nsa\n' "correct sort (alt)" || failed=1
	test_checker_should_print_ok " 3" "0 1 2 3" '' '' "already sorted" || failed=1
	test_checker_should_print_ko " 4" "3 0 1 2" $'pb\n' 'pb\n' "B is not empty" || failed=1
	test_checker_should_print_ko " 5" "3 2 0 1" $'sa\n' 'sa\n' "min is not at the top of A" || failed=1
	test_checker_should_print_ko " 6" "0 2 3 1" '' '' "A is not sorted" || failed=1

	return $failed
}

############# COMBINED RANDOM TESTS #############

run_combined_random_tests()
{
	local failed=0

	echo ""
	echo -e "${GREY}--- push_swap + checker combined tests (500 random numbers) ---${NC}\n"
	
	for i in $(seq 1 10); do
		test_num=$(printf "%2d" "$i")
		test_combined_random "$test_num" || failed=1
	done

	return $failed
}

test_combined_random()
{
	local test_num="$1"
	
	# Generate random stack
	local stack=$(shuf --input-range=0-2147483647 -n 500 | tr '\n' ' ')
	
	# Run push_swap | checker
	eval "$PUSH_SWAP $stack" | eval "$CHECKER $stack" > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "OK\n" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	# Count moves
	local moves=$(eval "$PUSH_SWAP $stack" 2>/dev/null | wc -l | tr -d ' ')
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$PUSH_SWAP [500 random] | $CHECKER [500 random]")
	local col2=$(printf "%-${COL2_WIDTH}s" "moves: $moves")
	local msg="should print 'OK\\n' to stdout and return 0"
	
	if [ "$stdout_got" = "$stdout_exp" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${GREEN}✔${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		return 0
	else
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${RED}✖${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

############# TEST FUNCTIONS #############

test_should_do_nothing()
{
	local program="$1"
	local test_num="$2"
	
	$program < /dev/null > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$program")
	local col2=$(printf "%-${COL2_WIDTH}s" "no arg")
	local msg="should print nothing and return 0"
	
	if [ "$stdout_got" = "$stdout_exp" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}.................${NC} ${GREEN}✔${NC}"
		return 0
	else
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}.................${NC} ${RED}✖${NC}"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_should_throw_error()
{
	local program="$1"
	local test_num="$2"
	local args="$3"
	local description="$4"
	
	eval "$program $args" < /dev/null > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "Error\n" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$program $args")
	local col2=$(printf "%-${COL2_WIDTH}s" "$description")
	local msg="should print 'Error\\\n' to stderr and return > 0"
	
	if [ "$stderr_got" = "$stderr_exp" ] && [ "$stdout_got" = "$stdout_exp" ] && [ $ret -ne 0 ]; then
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}...${NC} ${GREEN}✔${NC}"
		return 0
	else
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}...${NC} ${RED}✖${NC}"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_should_work()
{
	local program="$1"
	local test_num="$2"
	local args="$3"
	local description="$4"
	
	eval "$program $args" < /dev/null > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$program $args")
	local col2=$(printf "%-${COL2_WIDTH}s" "$description")
	local msg="should print to stdout and return 0"
	
	if [ -n "$stdout_got" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}...............${NC} ${GREEN}✔${NC}"
		return 0
	else
		echo -e "Test ${test_num}: ${BLUE}${col1}${NC} ⇢ ${col2} ⇢ ${msg} ${GRAY}...............${NC} ${RED}✖${NC}"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_checker_invalid_instruction()
{
	local test_num="$1"
	local args="$2"
	local stdin_input="$3"
	local display_stdin="$4"
	local description="$5"
	
	printf '%s' "$stdin_input" | eval "$CHECKER $args" > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "Error\n" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$CHECKER $args << \"${display_stdin}\"")
	local col2=$(printf "%-${COL2_WIDTH}s" "$description")
	local msg="should print 'Error\\n' to stderr and return > 0"
	
	if [ "$stderr_got" = "$stderr_exp" ] && [ "$stdout_got" = "$stdout_exp" ] && [ $ret -ne 0 ]; then
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}...${NC} ${GREEN}✔${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		return 0
	else
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}...${NC} ${RED}✖${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_checker_should_print_ok()
{
	local test_num="$1"
	local args="$2"
	local stdin_input="$3"
	local display_stdin="$4"
	local description="$5"
	
	printf '%s' "$stdin_input" | eval "$CHECKER $args" > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "OK\n" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$CHECKER $args << \"${display_stdin}\"")
	local col2=$(printf "%-${COL2_WIDTH}s" "$description")
	local msg="should print 'OK\\n' to stdout and return 0"
	
	if [ "$stdout_got" = "$stdout_exp" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${GREEN}✔${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		return 0
	else
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${RED}✖${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_checker_should_print_ko()
{
	local test_num="$1"
	local args="$2"
	local stdin_input="$3"
	local display_stdin="$4"
	local description="$5"
	
	printf '%s' "$stdin_input" | eval "$CHECKER $args" > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "KO\n" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$CHECKER $args << \"${display_stdin}\"")
	local col2=$(printf "%-${COL2_WIDTH}s" "$description")
	local msg="should print 'KO\\n' to stdout and return 0"
	
	if [ "$stdout_got" = "$stdout_exp" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${GREEN}✔${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		return 0
	else
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${RED}✖${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

test_combined_random()
{
	local test_num="$1"
	
	# Generate random stack
	local stack=$(shuf --input-range=0-2147483647 -n 500 | tr '\n' ' ')
	
	# Run push_swap | checker
	eval "$PUSH_SWAP $stack" | eval "$CHECKER $stack" > "$STDOUT_GOT" 2> "$STDERR_GOT"
	local ret=$?
	
	local stdout_got=$(cat -e "$STDOUT_GOT")
	local stderr_got=$(cat -e "$STDERR_GOT")
	
	printf "%b" "OK\n" > "$STDOUT_EXP"
	local stdout_exp=$(cat -e "$STDOUT_EXP")
	printf "%b" "" > "$STDERR_EXP"
	local stderr_exp=$(cat -e "$STDERR_EXP")
	
	# Count moves
	local moves=$(eval "$PUSH_SWAP $stack" 2>/dev/null | wc -l)
	
	local col1=$(printf "%-${COL1_WIDTH}s" "$PUSH_SWAP [500 random] | $CHECKER [500 random]")
	local col2=$(printf "%-${COL2_WIDTH}s" "moves: $moves")
	local msg="should print 'OK\\n' to stdout and return 0"
	
	if [ "$stdout_got" = "$stdout_exp" ] && [ "$stderr_got" = "$stderr_exp" ] && [ $ret -eq 0 ]; then
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${GREEN}✔${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		return 0
	else
		printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}........${NC} ${RED}✖${NC}\n" "$test_num" "$col1" "$col2" "$msg"
		echo -e "    ${RED}Stdout got: '$stdout_got'${NC}"
		echo -e "    ${RED}Stdout exp: '$stdout_exp'${NC}"
		echo -e "    ${RED}Stderr got: '$stderr_got'${NC}"
		echo -e "    ${RED}Stderr exp: '$stderr_exp'${NC}"
		echo -e "    ${RED}Return code: $ret${NC}"
		return 1
	fi
}

############# EXEC #############
main
############# EXEC #############