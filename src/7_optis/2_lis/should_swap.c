#include "stack.h"
#include "lis_priv.h"
# include "debug.h"	// TMP: remove before submit

static void	print_future(size_t depth, bool print_new_value, uint value, uint new_value);	// TMP: remove before submit

uint	future(t_stack *stack, size_t index, size_t depth, uint stop_value)
{
	uint	current;
	uint	second;
	uint	third;
	uint	future_third;

	current = stack_get_value(stack, (long)index);
	print_future(depth, false, current, 0);
	if (current == stop_value)
	{
		log_debug("future", depth, "[%zu] = %u => 🚦 Stopping, stop_value = current = %u\n", index, current, stop_value);
		print_future(depth, true, current, current);
		return (current);
	}
	if (index > stack->len)
	{
		log_debug("future", depth, "[%zu] = %u => 🚦 Stopping, index (%zu) > stack->len (%zu)\n", index, current, index, stack->len);
		print_future(depth, true, current, current);
		return (current);
	}
	second = stack_get_value(stack, (long)index + 1);
	if (current < second)
	{
		log_debug("future", depth, "[%zu] = %u => 🚦 Stopping, current (%u) < second (%u)\n", index, current, current, second);
		print_future(depth, true, current, current);
		return (current);
	}
	third = stack_get_value(stack, (long)index + 2);
	if (current < third)
	{
		log_debug("future", depth, "[%zu] = %u => 🪄 Swapping, current (%u) > second (%u) && current (%u) < third (%u)\n", index, current, current, second, current, third);
		print_future(depth, true, current, current);
		return (second);
	}
	future_third = future(stack, index + 2, depth + 1, stop_value);
	if (current < future_third)
	{
		log_debug("future", depth, "[%zu] = %u => 🪄 Swapping, current (%u) > second (%u) && current (%u) < future(third) (%u)\n", index, current, current, second, current, future_third);
		print_future(depth, true, current, current);
		return (second);
	}
	log_debug("future", depth, "[%zu] = %u => 🚦 Stopping, current (%u) > third (%u) (or is future value)\n", index, current, current, second);
	print_future(depth, true, current, second);
	return (second);
}



bool	should_swap(t_stack *stack, size_t index, uint stop_value, size_t depth)
{
	uint	previous;
	uint	current;
	uint	next;
	uint	third;

	// TODO: handle indexes 0 1 len - 1 len - 2 specifically
	current = stack_get_value(stack, (long)index);
	log_debug("should_swap", depth, "[%zu] = %u => Initial state => [%u |%u| %u %u]\n", index, current, stack_get_value(stack, (long)index + (long)stack->len - 1), current, stack_get_value(stack, (long)index + 1), stack_get_value(stack, (long)index + 2));
	stack_print_line(stack);
	fprintf(stderr, "\n");
	if (index > stack->len + 2)				// Stop case : only one stack cycle
		return (log_debug("should_swap", depth, "[%zu] = %u => %sindex (%zu) > stack->len (%zu) + 2%s\n", index, current, RED, index, stack->len, NC), false);
	// if (current == stop_value)				// Stop case : avoid infinite loop
	// 	return (log_debug("should_swap", depth, "[%zu] = %u => %sstop_value reached (%u)%s\n", index, current, RED, stop_value, NC), false);
	(void)stop_value;
	previous = future(stack, index + stack->len - 1, depth + 1, current);
	next = future(stack, index + 1, depth + 1, current);;
	third = future(stack, index + 2, depth + 1, current);
	log_debug("should_swap", depth, "[%zu] = %u => Future state ==> [%u |%u| %u %u]\n", index, current, previous, current, next, third);
	if (current == 0)						// Special case => 0 => next must be greater than previous and third
	{
		if (next > previous && next > third)
			return (log_debug("should_swap", depth, "[%zu] = %u => %scurrent == 0 && next (%u) > previous (%u) && next(%u) > third(%u)%s\n", index, current, GREEN, next, previous, next, third, NC), true);
	}
	else if (current < next)				// FALSE => Already sorted (current < next)
		return (log_debug("should_swap", depth, "[%zu] = %u => %scurrent != 0 && current < next (%u)%s\n", index, current, RED, next, NC), false);
	else if (current < third || third == 0)	// TRUE => current > 0 && (current < third || third == 0)
		return (log_debug("should_swap", depth, "[%zu] = %u => %scurrent < third (%u) || third == 0 %s\n", index, current, GREEN, third, NC), true);
	return (log_debug("should_swap", depth, "[%zu] = %u => %s(current == 0 && (next (%u) < previous (%u) || next < third (%u))) || current > next && current > third && third != 0%s\n", index, current, RED, next, previous, third, NC), false);
}

// TMP: remove before submit
static void	print_future(size_t depth, bool print_new_value, uint value, uint new_value)
{
	if (print_new_value && value == new_value)
		log_debug("future", depth, "%s%u -> %u%s\n", GREY, value, new_value, NC);
	else if (print_new_value && value != new_value)
		log_debug("future", depth, "%s%u -> %s%u%s\n", GREY, value, GREEN, new_value, NC);
	else
		log_debug("future", depth, "%s%u...%s\n", GREY, value, NC);
}



/* ---------- SWAP TESTS ---------- */

static bool	is_swappable(t_stack *stack, size_t index, uint prev, uint curr, uint next, uint third, size_t depth)
{
	uint	next_prev;
	uint	next_curr;
	uint	next_next;
	uint	next_third;

	if (next == 0 || third == 0)
	{
		next_prev = stack_get_value(stack, (long)index);
		next_curr = stack_get_value(stack, (long)index + 1);
		next_next = stack_get_value(stack, (long)index + 2);
		next_third = stack_get_value(stack, (long)index + 3);
		if (is_swappable(stack, index + 1, next_prev, next_curr, next_next, next_third, depth + 1))
		{
			log_debug("is_swappable", depth, "[%u |%u| %u %u] %s next == 0 and next is swappable%s\n", prev, curr, next, third, RED, NC);
			return (false);
		}
	}
	if (curr == 0)
	{
		if (next > prev && next > third)
		{
			log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr == 0   && next > prev && next > third%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC);
			return (true);
		}
		log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr == 0   && (next < prev || next < third)%s\n", prev, curr, next, third, RED, NC);
		return (false);
	}
	else if (curr < next)
	{
		log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr < next%s\n", prev, curr, next, third, RED, NC);
		return (false);
	}
	else if (curr < third || third == 0)
	{
		log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr > next && (curr < third || third == 0)%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC);
		return (true);
	}
	log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr > next && (curr > third && third != 0)%s\n", prev, curr, next, third, RED, NC);
	return (false);
}

void	test_swaps(t_stack *stack)
{
	size_t	i;
	uint	prev;
	uint	curr;
	uint	next;
	uint	third;
	size_t	last_swap_index;
	size_t	swaps;
	size_t	conflicts;
	bool	first_swappd;

	i = 0;
	last_swap_index = 0;
	swaps = 0;
	conflicts = 0;
	first_swappd = false;
	while (i < stack->len)
	{
		prev = stack_get_value(stack, (long)i - 1);
		curr = stack_get_value(stack, (long)i);
		next = stack_get_value(stack, (long)i + 1);
		third = stack_get_value(stack, (long)i + 2);
		if (is_swappable(stack, i, prev, curr, next, third, 1))
		{
			if (i == 0)
				first_swappd = true;
			if (swaps > 0 && last_swap_index == i - 1)
				conflicts++;
			if (first_swappd && i == stack->len - 1)
				conflicts++;
			swaps++;
			last_swap_index = i;
		}
		i++;
	}
	log_debug("test_swaps", 0, "Swaps availables = %zu | conflicts = %zu\n", swaps, conflicts);
}
