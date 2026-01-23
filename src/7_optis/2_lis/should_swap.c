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
	uint	previous;
	uint	current;
	uint	next;
	uint	third;
	uint	future_third;

	// TODO: handle indexes 0 1 len - 1 len - 2 specifically
	log_debug("should_swap", 0, "index %zu of ", index);
	stack_print_line(stack);
	if (index > stack->len)
		return (false);
	current = stack_get_value(stack, index);
	next = stack_get_value(stack, index + 1);
	third = stack_get_value(stack, index + 2);
	if (current == 0)
	{
		previous = stack_get_value(stack, index + stack->len - 1);
		log_debug("should_swap", 0, "previous (index = %zu) = %u\n", index + stack->len - 1, previous);
		if (next < previous)
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "false (%scurrent == 0 && previous > next%s)\n", RED, NC);
			return (false);
		}
		if (next > third)						// 0 && next > third
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent == 0 && previous < next && next > third%s)\n", GREEN, NC);
			return (true);
		}
		future_third = future(stack, index + 2, 1, current);
		if (next > future_third)				// 0 && next > future(third)
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent == 0 && previous < next && next > future(third)%s)\n", GREEN, NC);
			return (true);
		}
	}
	else if (current < next && next < third)		// Already sorted
	{
		log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
		fprintf(stderr, "false (%scurrent < next && next < third%s)\n", RED, NC);
		return (false);
	}
	else if (current > next)
	{
		if (current < third)					// OK with current third value (non-zero)
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent > next && current < third%s)\n", GREEN, NC);
			return (true);
		}
		if (third == 0)							// OK with current third value (0)
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent > next && third == 0%s)\n", GREEN, NC);
			return (true);
		}
		third = future(stack, index + 2, 1, current);
		if (current < third)					// OK with future third value
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent > next && current < future(third)%s)\n", GREEN, NC);
			return (true);
		}
		if (third == 0)							// OK with future third value (0)
		{
			log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
			fprintf(stderr, "🍀 true (%scurrent > next && future(third) == 0%s)\n", GREEN, NC);
			return (true);
		}
	}
	log_debug("should_swap", 0, "index %zu [%u %u %u] => ", index, current, next, third);
	fprintf(stderr, "false\n");
	return (false);
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
