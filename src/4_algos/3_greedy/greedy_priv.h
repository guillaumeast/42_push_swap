#ifndef GREEDY_PRIV_H
# define GREEDY_PRIV_H

# include "stack.h"
# include <stddef.h>

typedef struct s_cost
{
	size_t	rotate;
	size_t	reverse;
}	t_cost;

typedef struct s_cost_choice
{
	t_cost	opti;
	t_cost	bad;
}	t_cost_choice;

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

typedef struct s_insert
{
	size_t			from_index;
	size_t			target_index;
	t_total_cost	cost;
}	t_insert;

t_total_cost	get_best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b);

#endif
