#include "lis_priv.h"
#include "stack.h"
#include "stack_ops.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

static bool	is_swappable(t_stack *stack, size_t index, uint prev, uint curr, uint next, uint third, size_t depth);

bool	swap_stack(t_stack *dst, t_stack *src, bool **ret_swaps_array, size_t *ret_count)
{
	size_t	i;
	uint	prev;
	uint	curr;
	uint	next;
	uint	third;

	fprintf(stderr, "\n");
	log_debug("swap_stack", 0, "%sInitial stack (offset = %zu) => ", BLUE, src->offset);
	stack_print_line(src);
	fprintf(stderr, "%s\n", NC);
	*ret_swaps_array = malloc(src->len * sizeof ** ret_swaps_array);
	if (!*ret_swaps_array)
		return (false);
	ft_memset(*ret_swaps_array, false, src->len * sizeof ** ret_swaps_array);
	if (!stack_dup(dst, src))
		return (false);
	i = 0;
	*ret_count = 0;
	while (i < dst->len)
	{
		prev = stack_get_value(src, (long)i - 1);
		curr = stack_get_value(src, (long)i);
		next = stack_get_value(src, (long)i + 1);
		third = stack_get_value(src, (long)i + 2);
		if (is_swappable(src, i, prev, curr, next, third, 1))
		{
			(*ret_swaps_array)[curr] = true;
			(*ret_count)++;
			stack_swap(dst);
			stack_rotate(dst, 2);
			i += 2;
		}
		else
		{
			stack_rotate(dst, 1);
			i++;
		}
	}
	stack_reverse_rotate(dst, i);
	log_debug("swap_stack", 0, "%sSwaps (%zu) => ", BLUE, *ret_count);
	print_bool_array(*ret_swaps_array, src->len);
	log_debug("swap_stack", 0, "%sSwapped stack (offset = %zu) => ", BLUE, dst->offset);
	stack_print_line(dst);
	fprintf(stderr, "%s\n", NC);
	return (true);
}

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

bool	test_swaps(t_stack *dst, t_stack *src)
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
	bool	*swaped;
	size_t	swap_count;

	i = 0;
	last_swap_index = 0;
	swaps = 0;
	conflicts = 0;
	first_swappd = false;
	while (i < src->len)
	{
		prev = stack_get_value(src, (long)i - 1);
		curr = stack_get_value(src, (long)i);
		next = stack_get_value(src, (long)i + 1);
		third = stack_get_value(src, (long)i + 2);
		if (is_swappable(src, i, prev, curr, next, third, 1))
		{
			if (i == 0)
				first_swappd = true;
			if (swaps > 0 && last_swap_index == i - 1)
				conflicts++;
			if (first_swappd && i == src->len - 1)
				conflicts++;
			swaps++;
			last_swap_index = i;
		}
		i++;
	}
	if (conflicts > 0)
		log_debug("test_swaps", 0, "‼️ Swaps availables = %zu | %sconflicts = %zu%s\n", swaps, RED, conflicts, NC);
	else
		log_debug("test_swaps", 0, "Swaps availables = %zu | %sconflicts = %zu%s\n", swaps, GREEN, conflicts, NC);
	return (swap_stack(dst, src, &swaped, &swap_count));
}
