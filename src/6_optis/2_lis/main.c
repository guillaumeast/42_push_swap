#include "stack.h"
#include "lis_priv.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit
# include <print.h>	// TMP: remove before submit

# define DEBUG_DEPTH 0

static bool	lis_best_swaps_and_index(t_lis *lis, const t_stack *stack);
static bool	lis_best_index(t_lis *lis, const t_stack *stack, t_swaps *swaps);
static void	keep_best_lis(t_lis *dst, t_lis *a, t_lis *b);

bool	lis_compute_both(const t_stack *stack, t_lis *lis, t_lis *lis_swap)
{
	print_title("lis_compute_both()");
	if (!lis_best_index(lis, stack, NULL))
		return (false);
	if (!lis_best_swaps_and_index(lis_swap, stack))
		return (lis_free(lis), false);
	print_pass("swaps                    ⇢ %3zu ⇢ ", lis_swap->swap_count);
	if (should_print(LOG))
	{
		print_bool_array(lis_swap->swap, NULL, stack->len, GREY);
		fprintf(stderr, "%s\n", NC);
	}
	if (should_print_as(RESULT) == LOG)
	{
		if (lis_swap->keep_count > lis->keep_count)
			print_result_mid(false, "lis optimized with swaps ⇢ %3zu ⇢ ", lis_swap->keep_count);
		else
			print_result_mid(false, "lis optimized with swaps ⇢ %3zu ⇢ ", lis_swap->keep_count);
		print_bool_array(lis_swap->keep, NULL, stack->len, GREY);
		fprintf(stderr, "%s\n", NC);
		print_result_bot(true);
	}
	else
		print_result("lis optimized with swaps ⇢ %3zu ⇢ %zu", lis->keep_count, lis_swap->keep_count);
	return (true);
}

static bool	lis_best_swaps_and_index(t_lis *lis, const t_stack *stack)
{
	t_swapped	swapped_0_off;
	t_swapped	swapped_0_on;
	t_lis		lis_1;
	t_lis		lis_2;
	bool		success;

	print_title("lis_best_swaps_and_index()");
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
	print_result_mid(false, "Best swapped lis (i %3zu) ⇢ %3zu ⇢ ", lis->start_index, lis->keep_count);
	if (should_print(RESULT))
	{
		print_bool_array(lis->keep, NULL, stack->len, GREY);
		fprintf(stderr, "%s\n", NC);
	}
	print_result_bot(true);
	return (true);
}

static bool	lis_best_index(t_lis *lis, const t_stack *stack, t_swaps *swaps)
{
	t_lis	current_lis;
	size_t	i;

	print_title("lis_best_index()");
	if (!get_lis(lis, stack, 0, swaps))
	{
		print_error("Unable to compute lis for index 0\n");
		return (false);
	}
	i = 1;
	while (i < stack->len)
	{
		if (!get_lis(&current_lis, stack, i, swaps))
		{
			print_error("Unable to compute lis for index %zu\n", i);
			return (lis_free(lis), false);
		}
		keep_best_lis(lis, lis, &current_lis);
		i++;
	}
	print_result_mid(false, "Best lis (index %3zu)     ⇢ %3zu ⇢ ", lis->start_index, lis->keep_count);
	if (should_print(RESULT))
	{
		print_bool_array(lis->keep, NULL, stack->len, GREY);
		fprintf(stderr, "%s\n", NC);
	}
	print_result_bot(true);
	return (true);
}

static void	keep_best_lis(t_lis *dst, t_lis *a, t_lis *b)
{
	print_title("keep_best_lis()");
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
	print_result("best lis kept            ⇢ %3zu", dst->keep_count);
}

