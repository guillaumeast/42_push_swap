#include "stack.h"
#include "lis_priv.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

# define DEBUG_DEPTH 0

static bool	lis_best_swaps_and_index(t_lis *lis, const t_stack *stack);
static bool	lis_best_index(t_lis *lis, const t_stack *stack, t_swaps *swaps);
static void	keep_best_lis(t_lis *dst, t_lis *a, t_lis *b);

bool	lis_compute_both(const t_stack *stack, t_lis *lis, t_lis *lis_swap)
{
	if (!lis_best_index(lis, stack, NULL))
		return (false);
	fprintf(stderr, "%s✔︎   1%s lis            ⇢ %s%3zu%s ⇢ %s", GREEN, GREY, GREEN, lis->keep_count, GREY, NC); print_bool_array(lis->keep, NULL, stack->len, GREEN); fprintf(stderr, "%s\n", NC);
	if (!lis_best_swaps_and_index(lis_swap, stack))
		return (lis_free(lis), false);
	fprintf(stderr, "%s✔︎   1%s lis with swaps ⇢ %s%3zu%s ⇢ %s", GREEN, GREY, GREEN, lis_swap->keep_count, GREY, NC); print_bool_array(lis_swap->keep, lis->keep, stack->len, GREEN); fprintf(stderr, "%s\n", NC);

	fprintf(stderr, "%s✔︎   1%s swaps          ⇢ %s%3zu%s ⇢ %s", GREEN, GREY, GREEN, lis_swap->swap_count, GREY, NC); print_bool_array(lis_swap->swap, NULL, stack->len, GREEN); fprintf(stderr, "%s\n", NC);
	return (true);
}

static bool	lis_best_swaps_and_index(t_lis *lis, const t_stack *stack)
{
	t_swapped	swapped_0_off;
	t_swapped	swapped_0_on;
	t_lis		lis_1;
	t_lis		lis_2;
	bool		success;

	if (!swap_stack(&swapped_0_off, stack, false))
		return (false);
	if (!swap_stack(&swapped_0_on, stack, true))
		return (swap_free(&swapped_0_off), false);
	if (!lis_best_index(&lis_1, &swapped_0_on.swapped, &swapped_0_on.swaps))
		return (swap_free(&swapped_0_off), swap_free(&swapped_0_on), false);
	success = lis_best_index(&lis_2, &swapped_0_off.swapped, &swapped_0_off.swaps);
	if (success)
		keep_best_lis(lis, &lis_1, &lis_2);
	swap_free(&swapped_0_off);
	swap_free(&swapped_0_on);
	return (true);
}

static bool	lis_best_index(t_lis *lis, const t_stack *stack, t_swaps *swaps)
{
	t_lis	current_lis;
	size_t	i;

	if (!get_lis(lis, stack, 0, swaps))
		return (false);
	i = 1;
	while (i < stack->len)
	{
		if (!get_lis(&current_lis, stack, i, swaps))
			return (lis_free(lis), false);
		keep_best_lis(lis, lis, &current_lis);
		i++;
	}
	return (true);
}

static void	keep_best_lis(t_lis *dst, t_lis *a, t_lis *b)
{
	if (a->keep_count > b->keep_count
		||	(a->keep_count == b->keep_count && a->swap_count < b->swap_count)
	)
	{
		lis_free(b);
		*dst = *a;
	}
	else
	{
		lis_free(a);
		*dst = *b;
	}
}

