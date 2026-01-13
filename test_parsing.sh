#!/bin/bash

# Colors
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
GRAY='\033[0;90m'
NC='\033[0m' # No Color

print_success()
{
	echo -e "${GREEN}✔${NC}"
}

print_error()
{
	local stdout_value="$1"
	local stderr_value="$2"
	local return_code="$3"
	
	echo -e "${RED}✖${NC}"
	echo -e "    ${RED}Stdout: '$stdout_value'${NC}"
	echo -e "    ${RED}Stderr: '$stderr_value'${NC}"
	echo -e "    ${RED}Return code: $return_code${NC}"
}

test_should_do_nothing()
{
	echo -ne "Test  1: ${YELLOW}./push_swap${NC}                                       -> no arg         ->    should print nothing and return 0 ${GRAY}...............${NC} "
	
	stdout=$(./push_swap 2>/dev/null)
	stderr=$(./push_swap 2>&1 >/dev/null)
	ret=$?
	
	if [ -z "$stdout" ] && [ -z "$stderr" ] && [ $ret -eq 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret"
	fi
}

test_should_throw_error()
{
	local test_num="$1"
	local command="$2"
	local description="$3"
	local dots="$4"
	
	echo -ne "Test ${test_num}: ${YELLOW}${command}${NC} ${description} should print 'Error' to stderr and return > 0 ${GRAY}${dots}${NC} "
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if echo "$stderr" | grep -q "Error" && [ $ret -ne 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret"
	fi
}

test_should_work()
{
	local test_num="$1"
	local command="$2"
	local description="$3"
	local dots="$4"
	
	echo -ne "Test ${test_num}: ${YELLOW}${command}${NC} ${description} should print to stdout and return 0 ${GRAY}${dots}${NC} "
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if [ -n "$stdout" ] && [ $ret -eq 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret"
	fi
}

echo
echo "=== Parsing tests for push_swap ==="
echo

test_should_do_nothing

test_should_throw_error " 2" "./push_swap 1 2 3 1" "                              -> duplicate      ->   " "..."
test_should_throw_error " 3" "./push_swap \"\"" "                                   -> single empty   ->   " "..."
test_should_throw_error " 4" "./push_swap 1 \"\" 3 4" "                             -> empty arg      ->   " "..."
test_should_throw_error " 5" "./push_swap 1 + 3 4" "                              -> invalid '+'    ->   " "..."
test_should_throw_error " 6" "./push_swap 1 - 3 4" "                              -> invalid '-'    ->   " "..."
test_should_throw_error " 7" "./push_swap 1 2a3 4" "                              -> invalid '2a3'  ->   " "..."
test_should_throw_error " 8" "./push_swap 1 2 -2147483649" "                      -> int underflow  ->   " "..."
test_should_throw_error " 9" "./push_swap 1 2 2147483648" "                       -> int overflow   ->   " "..."
test_should_throw_error "10" "./push_swap 1 2 +2147483648" "                      -> int overflow   ->   " "..."
test_should_throw_error "11" "./push_swap 1 a2 3" "                               -> invalid start  ->   " "..."
test_should_throw_error "12" "./push_swap \"\" \"\" \"\" \"\"" "                          -> all empty args ->   " "..."

test_should_work "13" "./push_swap -2147483648 \"5 1\" +2147483647" "        -> space          ->   " "............."
test_should_work "14" "./push_swap -2147483648 \" 5 1\" +2147483647" "       -> leading space  ->   " "............."
test_should_work "15" "./push_swap -2147483648 \"5 1 \" +2147483647" "       -> trailing space ->   " "............."
test_should_work "16" "./push_swap -2147483648 \"   5   1   \" +2147483647" "-> multi spaces   ->   " "............."

echo
echo "=== End of tests ==="
