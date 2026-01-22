#ifndef LIS_PRIV_H
# define LIS_PRIV_H

# include "stack.h"
# include "lis.h"
# include <stddef.h>

typedef struct s_swapped_stack
{
	t_stack	stack;			// Stack (swapped)
	bool	*swaps;			// Value-indexed array of executed swaps
	bool	first_swapped;	// True if stack[0] or stack[1] has been swapped
}	t_swapped_stack;

/* ---------- lis_best.c ---------- */

bool	lis_best_between(t_swapped_stack *v1, t_swapped_stack *v2, t_lis *lis);
bool	lis_best(t_stack *stack, bool *swaps, t_lis *lis);

/* ---------- lis.c ---------- */

bool	lis_compute(t_lis *lis, t_stack *stack, bool *swap, size_t start_index);

#endif
