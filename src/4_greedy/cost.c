#include "cost.h"
#include "libft.h"

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

static void	get_cost(size_t stack_len, size_t index, t_cost_choice *cost);
static void	cost_add(t_cost *a, t_cost *b, t_total_cost *res);

t_total_cost	get_best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b)
{
	t_cost_choice	a_cost;
	t_cost_choice	b_cost;
	t_total_cost	best;
	t_total_cost	current;

	get_cost(a->size, i_a, &a_cost);
	get_cost(b->size, i_b, &b_cost);
	cost_add(&a_cost.opti, &b_cost.opti, &best);
	cost_add(&a_cost.opti, &b_cost.bad, &current);
	if (current.total < best.total)
		best = current;
	cost_add(&a_cost.bad, &b_cost.opti, &current);
	if (current.total < best.total)
		return (current);
	return (best);
}

static void	get_cost(size_t stack_len, size_t index, t_cost_choice *cost)
{
	if (index <= stack_len / 2)
	{
		cost->opti.rotate = index;
		cost->opti.reverse = 0;
		cost->bad.rotate = 0;
		cost->bad.rotate = stack_len - index;
	}
	else
	{
		cost->opti.rotate = 0;
		cost->opti.reverse = stack_len - index;
		cost->bad.rotate = index;
		cost->bad.reverse = 0;
	}
}

static void	cost_add(t_cost *a, t_cost *b, t_total_cost *res)
{
	res->rr = (size_t)ft_min((int)a->rotate, (int)b->rotate);
	res->rrr = (size_t)ft_min((int)a->reverse, (int)b->reverse);
	res->ra = a->rotate - res->rr;
	res->rb = b->rotate - res->rr;
	res->rra = a->reverse - res->rrr;
	res->rrb = b->reverse - res->rrr;
	res->total = res->rr + res->rrr + res->ra + res->rb + res->rra + res->rrb;
}
