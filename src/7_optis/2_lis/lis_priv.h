#ifndef LIS_PRIV_H
# define LIS_PRIV_H

# include "stack.h"
# include "lis.h"

typedef struct s_swaps
{
	uint	*from;
	uint	*to;
	size_t	count;
}	t_swaps;

bool	lis_best(t_lis *lis, const t_stack *stack, t_swaps *swaps);

#endif
