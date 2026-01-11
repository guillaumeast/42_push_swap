#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
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
	local error_message="$4"
	
	echo -e "${RED}✖${NC}"
	echo -e "    ${RED}${error_message}${NC}"
	echo -e "    ${RED}Stdout: '$stdout_value'${NC}"
	echo -e "    ${RED}Stderr: '$stderr_value'${NC}"
	echo -e "    ${RED}Return code: $return_code${NC}"
}

test_should_do_nothing()
{
	echo -n "Test  1: [./push_swap] (no arguments) ... "
	
	stdout=$(./push_swap 2>/dev/null)
	stderr=$(./push_swap 2>&1 >/dev/null)
	ret=$?
	
	if [ -z "$stdout" ] && [ -z "$stderr" ] && [ $ret -eq 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret" "[./push_swap] should print nothing and return 0"
	fi
}

test_should_throw_error()
{
	local test_name="$1"
	local command="$2"
	
	echo -n "$test_name ... "
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if echo "$stderr" | grep -q "Error" && [ $ret -ne 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret" "[$command] should print 'Error' to stderr and return > 0"
	fi
}

test_should_work()
{
	local test_name="$1"
	local command="$2"
	local error_message="$3"
	
	echo -n "$test_name ... "
	
	stdout=$(eval "$command" 2>/dev/null)
	stderr=$(eval "$command" 2>&1 >/dev/null)
	ret=$?
	
	if [ -n "$stdout" ] && [ $ret -eq 0 ]; then
		print_success
	else
		print_error "$stdout" "$stderr" "$ret" "$error_message"
	fi
}

echo
echo "=== Parsing tests for push_swap ==="
echo

test_should_do_nothing

test_should_throw_error \
	"Test  2: [./push_swap 1 2 3 1] (duplicate)" \
	"./push_swap 1 2 3 1"

test_should_throw_error \
	"Test  3: [./push_swap 1 \"\" 3 4] (empty string)" \
	"./push_swap 1 \"\" 3 4"

test_should_throw_error \
	"Test  4: [./push_swap 1 + 3 4] (invalid '+')" \
	"./push_swap 1 + 3 4"

test_should_throw_error \
	"Test  5: [./push_swap 1 - 3 4] (invalid '-')" \
	"./push_swap 1 - 3 4"

test_should_throw_error \
	"Test  6: [./push_swap 1 2a3 4] (invalid '2a3')" \
	"./push_swap 1 2a3 4"

test_should_throw_error \
	"Test  7: [./push_swap 1 2 -2147483649] (int underflow)" \
	"./push_swap 1 2 -2147483649"

test_should_throw_error \
	"Test  8: [./push_swap 1 2 2147483648] (int overflow)" \
	"./push_swap 1 2 2147483648"

test_should_throw_error \
	"Test  9: [./push_swap 1 2 +2147483648] (int overflow with +)" \
	"./push_swap 1 2 +2147483648"

test_should_work \
	"Test 10: [./push_swap -2147483648 \"5 1\" +2147483647] (valid arguments)" \
	"./push_swap -2147483648 \"5 1\" +2147483647" \
	"[./push_swap -2147483648 \"5 1\" +2147483647] should print something to stdout and return 0"

test_should_work \
	"Test 11: [./push_swap -2147483648 \" 5 1\" +2147483647] (valid arguments)" \
	"./push_swap -2147483648 \" 5 1\" +2147483647" \
	"[./push_swap -2147483648 \" 5 1\" +2147483647] should print something to stdout and return 0"

test_should_work \
	"Test 10: [./push_swap -2147483648 \"5 1 \" +2147483647] (valid arguments)" \
	"./push_swap -2147483648 \"5 1 \" +2147483647" \
	"[./push_swap -2147483648 \"5 1 \" +2147483647] should print something to stdout and return 0"

test_should_work \
	"Test 10: [./push_swap -2147483648 \"   5   1   \" +2147483647] (valid arguments)" \
	"./push_swap -2147483648 \"   5   1   \" +2147483647" \
	"[./push_swap -2147483648 \"   5   1   \" +2147483647] should print something to stdout and return 0"

echo
echo "=== End of tests ==="
