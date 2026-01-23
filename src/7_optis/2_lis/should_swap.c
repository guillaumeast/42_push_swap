#include "stack.h"
# include "debug.h"	// TMP: remove before submit

static void	print_future(size_t depth, bool print_new_value, uint value, uint new_value);	// TMP: remove before submit

uint	future(t_stack *stack, size_t index, size_t depth, uint stop_value)
{
	uint	current;
	uint	second;
	uint	third;

	current = stack_get_value(stack, index);
	print_future(depth, false, current, 0);
	if (current == stop_value)
	{
		log_debug("future", depth, "🚦 Stopping, stop_value = current = %u\n", stop_value);
		print_future(depth, true, current, current);
		return (current);
	}
	if (index > stack->len)
	{
		print_future(depth, true, current, current);
		return (current);
	}
	second = stack_get_value(stack, index + 1);
	if (current < second)
	{
		print_future(depth, true, current, current);
		return (current);
	}
	third = stack_get_value(stack, index + 2);
	if (current > third || current > future(stack, index + 2, depth + 1, stop_value))
	{
		print_future(depth, true, current, current);
		return (current);
	}
	print_future(depth, true, current, second);
	return (second);
}

bool	should_swap(t_stack *stack, size_t index)
{
	uint	current;
	uint	second;
	uint	third;

	if (index > stack->len)
		return (false);
	current = stack_get_value(stack, index);
	second = stack_get_value(stack, index + 1);
	third = stack_get_value(stack, index + 2);
	if (current < second)
		return (false);
	return (current > third || current > future(stack, index + 2, 1, current));
}

// TMP: remove before submit
static void	print_future(size_t depth, bool print_new_value, uint value, uint new_value)
{
	if (print_new_value && value == new_value)
		log_debug("future", depth, "%s%u -> %u%s\n", GREY, value, new_value, NC);
	else if (print_new_value && value != new_value)
		log_debug("future", depth, "%s%u -> %s%u%s \n", GREY, value, GREEN, new_value, NC);
	else
		log_debug("future", depth, "%s%u...%s\n", GREY, value, NC);
}
