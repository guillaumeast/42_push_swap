#include "lis_priv.h"
#include "lis_priv.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

static bool	lis_1_is_better(t_lis *lis_1, t_lis *lis_2);

bool	lis_best_between(t_swapped_stack *v1, t_swapped_stack *v2, t_lis *lis)
{
	t_lis	lis1;
	t_lis	lis2;

	// fprintf(stderr, "[🔦 DEBUG] => lis_best_between()...\n");		// TMP: remove before submit
	if (!lis_best(&v1->stack, v1->swaps, &lis1))
		return (false);
	if (!lis_best(&v2->stack, v2->swaps, &lis2))
		return (lis_free(&lis1), false);
	if (lis_1_is_better(&lis1, &lis2))
	{
		lis_free(&lis2);
		*lis = lis1;
	}
	else
	{
		lis_free(&lis1);
		*lis = lis2;
	}
	// fprintf(stderr, "[🔦 DEBUG] => lis_best_between() done!\n");	// TMP: remove before submit
	// lis_print(lis, v1->stack.len);								// TMP: remove before submit
	return (true);
}

/*
*	Computes the best lis from a stack.
*
*	Bruteforces each index LIS and keeps the best one.
*	Useless swaps are removed.
*
*	@note: swaps is optional.
*	@note: swaps is borrowed (lis creates its own copy of it).
*/
bool	lis_best(t_stack *stack, bool *swaps, t_lis *lis)
{
	size_t	start_index;
	t_lis	current_lis;

	// fprintf(stderr, "[🔦 DEBUG] ===> lis_compute_best()...\n");		// TMP: remove before submit
	// stack_print(stack, stack);								// TMP: remove before submit
	if (!lis_compute(lis, stack, swaps, 0))
		return (lis_free(lis), false);
	start_index = 1;
	while (start_index < stack->len)
	{
		if (!lis_compute(&current_lis, stack, swaps, start_index))
			return (lis_free(lis), false);
		if (lis_1_is_better(&current_lis, lis))
		{
			lis_free(lis);
			*lis = current_lis;
		}
		else
			lis_free(&current_lis);
		start_index++;
	}
	// lis_print(lis, stack->len);								// TMP: remove before submit
	return (true);
}

static bool	lis_1_is_better(t_lis *lis_1, t_lis *lis_2)
{
	if (lis_1->keep_count == lis_2->keep_count)
		return (lis_1->swap_count < lis_2->swap_count);
	return (lis_1->keep_count > lis_2->keep_count);
}

void	lis_free(t_lis *lis)
{
	if (lis->keep)
		free(lis->keep);
	if (lis->swap)
		free(lis->swap);
}
