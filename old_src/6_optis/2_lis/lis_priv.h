#ifndef LIS_PRIV_H
# define LIS_PRIV_H

# include "stack.h"
# include "lis.h"

typedef struct s_swaps
{
	uint	*from;	// Owned
	uint	*to;	// Owned
	size_t	count;
}	t_swaps;

typedef struct s_swapped
{
	t_stack	original;	// Borrowed
	t_stack	swapped;	// Owned
	t_swaps	swaps;		// Owned
	bool	swap_first;
}	t_swapped;

/* ---------- lis.c ---------- */

bool	get_lis(t_lis *lis, const t_stack *stk, size_t i, const t_swaps *swaps);

/* ---------- swap.c ---------- */

bool	swap_stack(t_swapped *dst, const t_stack *src, bool swap_first);
void	swap_free(t_swapped *swapped);

#endif
