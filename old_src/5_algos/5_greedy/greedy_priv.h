#ifndef GREEDY_PRIV_H
# define GREEDY_PRIV_H

# include "stack.h"
# include <stddef.h>

typedef struct s_total
{
	size_t	rr;
	size_t	ra;
	size_t	rb;
	size_t	rrr;
	size_t	rra;
	size_t	rrb;
	size_t	total;
}	t_total;

t_total	best_cost(const t_stack *a, size_t i_a, const t_stack *b, size_t i_b);

#endif
