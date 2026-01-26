#include "libft.h"
#include "lis_priv.h"
#include "stack_ops.h"
#include <stdlib.h>
// # include "debug.h"	// TMP: remove before submit

# define DEBUG_DEPTH 3

static bool	init_swaps(t_swapped *dst, const t_stack *src, bool swap_first);
static bool	is_swappable(const t_stack *stack, size_t index, bool swap_first);
// static void	test_swap_conflicts(const t_stack *stack, bool swap_first);	// TMP: remove before submit

bool	swap_stack(t_swapped *dst, const t_stack *src, bool swap_first)
{
	size_t	i;

	if (!init_swaps(dst, src, swap_first))
		return (false);
	i = 0;
	dst->swaps.count = 0;
	while (i < src->len)
	{
		if (is_swappable(src, i, swap_first))
		{
			dst->swaps.from[dst->swaps.count] = stack_get_value(src, (long)i);
			dst->swaps.to[dst->swaps.count] = stack_get_value(src, (long)i + 1);
			dst->swaps.count++;
			stack_swap(&dst->swapped);
			stack_rotate(&dst->swapped, 2);
			i++;
		}
		else
			stack_rotate(&dst->swapped, 1);
		i++;
	}
	stack_reverse_rotate(&dst->swapped, dst->swapped.offset);
	// TMP: remove before submit
	// test_swap_conflicts(src, swap_first);
	// log_debug("swap_stack", DEBUG_DEPTH, "%sInitial stack   => ", BLUE); stack_print_line(src, NULL, BLUE); fprintf(stderr, "%s\n", NC);
	// log_debug("swap_stack", DEBUG_DEPTH, "%sSwapped stack   => ", BLUE); stack_print_line(&dst->swapped, src, BLUE); fprintf(stderr, "%s\n", NC);
	// log_debug("swap_stack", DEBUG_DEPTH, "%sRaw swaps   %3zu => [", BLUE, dst->swaps.count);
	// for (size_t j = 0; j < dst->swaps.count; j++)
	// {
	// 	fprintf(stderr, "%u", dst->swaps.from[j]);
	// 	if (j < dst->swaps.count - 1)
	// 		fprintf(stderr, " ");
	// }
	// fprintf(stderr, "]%s\n", NC);
	return (true);
}

static bool	init_swaps(t_swapped *dst, const t_stack *src, bool swap_first)
{
	dst->swaps.from = malloc(src->len * sizeof * dst->swaps.from);
	if (!dst->swaps.from)
		return (false);
	dst->swaps.to = malloc(src->len * sizeof * dst->swaps.to);
	if (!dst->swaps.to)
		return (free(dst->swaps.from), false);
	if (!stack_dup(&dst->swapped, src))
		return (free(dst->swaps.from), free(dst->swaps.to), false);
	dst->swaps.count = 0;
	dst->original = *src;
	dst->swap_first = swap_first;
	return (true);
}

static bool	is_swappable(const t_stack *stack, size_t index, bool swap_first)
{
	uint	prev;
	uint	curr;
	uint	next;
	uint	third;
	
	if (modulo((long)index, stack->len) == 0)
		return (swap_first);
	prev = stack_get_value(stack, (long)index - 1);
	curr = stack_get_value(stack, (long)index);
	if (index == (stack->len - 1) && is_swappable(stack, index + 1, swap_first))
	{
		next = stack_get_value(stack, (long)index + 2);
		third = stack_get_value(stack, (long)index + 1);
	}
	else
	{
		next = stack_get_value(stack, (long)index + 1);
		third = stack_get_value(stack, (long)index + 2);
		if ((next == 0 || third == 0) && is_swappable(stack, index + 1, swap_first))
			return (false);
	}
	if (curr == 0)
		return (next > prev && next > third);	// log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr == 0   && next > prev && next > third%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC); / log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr == 0   && (next < prev || next < third)%s\n", prev, curr, next, third, RED, NC);
	else if (curr < next)
		return (false);							// log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr < next%s\n", prev, curr, next, third, RED, NC);
	return (curr < third || third == 0);		// log_debug("is_swappable", depth, "[%u |%s%u%s| %u %u] %scurr > next && (curr < third || third == 0)%s\n", prev, GREEN, curr, NC, next, third, GREEN, NC); / // log_debug("is_swappable", depth, "[%u |%u| %u %u] %scurr > next && (curr > third && third != 0)%s\n", prev, curr, next, third, RED, NC);
}

void	swap_free(t_swapped *swapped)
{
	if (swapped->swapped.data)
		free(swapped->swapped.data);
	if (swapped->swaps.from)
		free(swapped->swaps.from);
	if (swapped->swaps.to)
		free(swapped->swaps.to);
}

// TMP: remove before submit
// static void	test_swap_conflicts(const t_stack *stack, bool swap_first)
// {
// 	size_t	i;
// 	size_t	swaps;
// 	size_t	last_swap_index;

// 	i = 0;
// 	swaps = 0;
// 	last_swap_index = 0;
// 	while (i < stack->len)
// 	{
// 		if (is_swappable(stack, i, swap_first))
// 		{
// 			if (swaps > 0 && last_swap_index == i - 1)
// 				fprintf(stderr, "%s‼️ Swap conflict between %s%u%s and %s%u%s\n", RED, YELLOW, stack->data[i - 1], RED, YELLOW, stack->data[i], NC);
// 			if (swap_first && i == stack->len - 1)
// 				fprintf(stderr, "%s‼️ Swap conflict between %s%u%s and %s%u%s\n", RED, YELLOW, stack->data[0], RED, YELLOW, stack->data[i], NC);
// 			swaps++;
// 			last_swap_index = i;
// 		}
// 		i++;
// 	}
// }
