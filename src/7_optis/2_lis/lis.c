#include "lis_priv.h"
#include "stack.h"
#include "stack_ops.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

# define DEBUG_DEPTH 0

static bool	swap_stack(t_stack *dst, const t_stack *src, t_swaps *swaps);
static bool	is_swappable(const t_stack *stack, size_t index);
static void	test_swap_conflicts(const t_stack *stack);	// TMP: remove before submit

bool	lis_compute_both(const t_stack *stack, t_lis *lis, t_lis *lis_swap)
{
	t_stack	swapped;
	t_swaps	swaps;
	bool	success;

	test_swap_conflicts(stack);
	if (!lis_best(lis, stack, NULL))
		return (false);
	if (!stack_dup(&swapped, stack))
		return (lis_free(lis), false);
	if (!swap_stack(&swapped, stack, &swaps))
		return (lis_free(lis), free(swapped.data), false);
	success = lis_best(lis_swap, &swapped, &swaps);
	// TMP: remove before submit
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sInitial stack   => ", BLUE); stack_print_line(stack, NULL, BLUE); fprintf(stderr, "%s\n", NC);
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sSwapped stack   => ", BLUE); stack_print_line(&swapped, stack, BLUE); fprintf(stderr, "%s\n", NC);
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sRaw swaps   %3zu => [", BLUE, swaps.count);
	for (size_t i = 0; i < swaps.count; i++)
	{
		fprintf(stderr, "%u", swaps.from[i]);
		if (i < swaps.count - 1)
			fprintf(stderr, " ");
	}
	fprintf(stderr, "]%s\n", NC);
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sInitial lis %3zu => ", GREEN, lis->keep_count); print_bool_array(lis->keep, NULL, stack->len, GREEN); fprintf(stderr, "%s\n", NC);
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sSwapped lis %3zu => ", GREEN, lis_swap->keep_count); print_bool_array(lis_swap->keep, lis->keep, stack->len, GREEN); fprintf(stderr, "%s\n", NC);
	log_debug("lis_compute_both", DEBUG_DEPTH, "%sFinal swaps %3zu => ", GREEN, lis_swap->swap_count); print_bool_array(lis_swap->swap, NULL, stack->len, GREEN); fprintf(stderr, "%s\n", NC);
	//
	if (!success)
		lis_free(lis);
	free(swapped.data);
	free(swaps.from);
	free(swaps.to);
	return (success);
}

static bool	swap_stack(t_stack *dst, const t_stack *src, t_swaps *swaps)
{
	size_t	i;

	swaps->from = malloc(src->len * sizeof * swaps->from);
	swaps->to = malloc(src->len * sizeof * swaps->to);
	if (!swaps->from || !swaps->to || !stack_dup(dst, src))
		return (free(swaps->from), free(swaps->to), false);
	i = 0;
	swaps->count = 0;
	while (i < dst->len)
	{
		if (is_swappable(src, i))
		{
			swaps->from[swaps->count] = stack_get_value(src, (long)i);
			swaps->to[swaps->count] = stack_get_value(src, (long)i + 1);
			swaps->count++;
			stack_swap(dst);
			stack_rotate(dst, 2);
			i++;
		}
		else
			stack_rotate(dst, 1);
		i++;
	}
	stack_reverse_rotate(dst, dst->offset);
	return (true);
}

static bool	is_swappable(const t_stack *stack, size_t index)
{
	uint	prev;
	uint	curr;
	uint	next;
	uint	third;
	
	prev = stack_get_value(stack, (long)index - 1);
	curr = stack_get_value(stack, (long)index);
	if (index == (stack->len - 1) && is_swappable(stack, index + 1))
	{
		next = stack_get_value(stack, (long)index + 2);
		third = stack_get_value(stack, (long)index + 1);
	}
	else
	{
		next = stack_get_value(stack, (long)index + 1);
		third = stack_get_value(stack, (long)index + 2);
		if ((next == 0 || third == 0) && is_swappable(stack, index + 1))
			return (false);
	}
	if (curr == 0)
		return (next > prev && next > third);	// log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr == 0   && next > prev && next > third%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC); / log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr == 0   && (next < prev || next < third)%s\n", prev, curr, next, third, RED, NC);
	else if (curr < next)
		return (false);							// log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr < next%s\n", prev, curr, next, third, RED, NC);
	return (curr < third || third == 0);		// log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr > next && (curr < third || third == 0)%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC); / // log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr > next && (curr > third && third != 0)%s\n", prev, curr, next, third, RED, NC);
}

void	lis_free(t_lis *lis)
{
	if (lis->keep)
		free(lis->keep);
	if (lis->swap)
		free(lis->swap);
}

// TMP: remove before submit
static void	test_swap_conflicts(const t_stack *stack)
{
	size_t	i;
	size_t	swaps;
	size_t	last_swap_index;
	bool	first_swapped;

	i = 0;
	swaps = 0;
	last_swap_index = 0;
	first_swapped = false;
	while (i < stack->len)
	{
		if (is_swappable(stack, i))
		{
			if (i == 0)
				first_swapped = true;
			if (swaps > 0 && last_swap_index == i - 1)
				fprintf(stderr, "%s‼️ Swap conflict between %s%u%s and %s%u%s\n", RED, YELLOW, stack->data[i - 1], RED, YELLOW, stack->data[i], NC);
			if (first_swapped && i == stack->len - 1)
				fprintf(stderr, "%s‼️ Swap conflict between %s%u%s and %s%u%s\n", RED, YELLOW, stack->data[0], RED, YELLOW, stack->data[i], NC);
			swaps++;
			last_swap_index = i;
		}
		i++;
	}
}
