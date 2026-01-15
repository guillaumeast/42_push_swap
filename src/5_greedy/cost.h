#ifndef COST_H
# define COST_H

# include "stack.h"
# include <stddef.h>

typedef struct s_total_cost
{
	size_t	rr;
	size_t	ra;
	size_t	rb;
	size_t	rrr;
	size_t	rra;
	size_t	rrb;
	size_t	total;
}	t_total_cost;

t_total_cost	get_best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b);

#endif
