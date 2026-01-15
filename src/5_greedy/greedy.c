#include "libft.h"
#include "moves.h"

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

static t_insert		get_next_insert(t_stack *from, t_stack *to);
static t_total_cost	best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b);
static void			get_cost(size_t stack_len, size_t idx, t_cost_choice *cost);
static void			cost_add(t_cost *a, t_cost *b, t_total_cost *res);

bool	greedy(t_stack *a, t_stack *b, t_buff *move_list)
{
	t_insert	next_insertion;

	while (b->len > 0)
	{
		next_insertion = get_next_insert(b, a);
		if (!rr(a, b, next_insertion.cost.rr, move_list))
			return (false);
		if (!ra(a, next_insertion.cost.ra, move_list))
			return (false);
		if (!rb(b, next_insertion.cost.rb, move_list))
			return (false);
		if (!rrr(a, b, next_insertion.cost.rrr, move_list))
			return (false);
		if (!rra(a, next_insertion.cost.rra, move_list))
			return (false);
		if (!rrb(b, next_insertion.cost.rrb, move_list))
			return (false);
		if (!pa(a, b, 1, move_list))
			return (false);
	}
	return (true);
}

static t_insert	get_next_insert(t_stack *from, t_stack *to)
{
	size_t		i;
	bool		best_is_set;
	t_insert	best;
	t_insert	current;
	uint		current_value;

	ft_bzero(&best, sizeof best);
	1 && (best_is_set = false, i = 0);
	while (i < from->len)
	{
		ft_bzero(&current, sizeof current);
		current.from_index = i;
		current_value = stack_get_value(from, i);
		current.target_index = stack_get_target_index(to, current_value);
		current.cost = best_cost(to, current.target_index, from, i);
		if (!best_is_set || current.cost.total < best.cost.total)
		{
			best = current;
			best_is_set = true;
		}
		i++;
		if (best.cost.total == 0)
			break ;
	}
	return (best);
}

static t_total_cost	best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b)
{
	t_cost_choice	a_cost;
	t_cost_choice	b_cost;
	t_total_cost	best;
	t_total_cost	current;

	get_cost(a->len, i_a, &a_cost);
	get_cost(b->len, i_b, &b_cost);
	cost_add(&a_cost.opti, &b_cost.opti, &best);
	cost_add(&a_cost.opti, &b_cost.bad, &current);
	if (current.total < best.total)
		best = current;
	cost_add(&a_cost.bad, &b_cost.opti, &current);
	if (current.total < best.total)
		return (current);
	return (best);
}

static void	get_cost(size_t stack_len, size_t idx, t_cost_choice *cost)
{
	if (idx <= stack_len / 2)
	{
		cost->opti.rotate = idx;
		cost->opti.reverse = 0;
		cost->bad.rotate = 0;
		cost->bad.reverse = stack_len - idx;
	}
	else
	{
		cost->opti.rotate = 0;
		cost->opti.reverse = stack_len - idx;
		cost->bad.rotate = idx;
		cost->bad.reverse = 0;
	}
}

static void	cost_add(t_cost *a, t_cost *b, t_total_cost *res)
{
	res->rr = (size_t)min((long)a->rotate, (long)b->rotate);
	res->rrr = (size_t)min((long)a->reverse, (long)b->reverse);
	res->ra = a->rotate - res->rr;
	res->rb = b->rotate - res->rr;
	res->rra = a->reverse - res->rrr;
	res->rrb = b->reverse - res->rrr;
	res->total = res->rr + res->rrr + res->ra + res->rb + res->rra + res->rrb;
}
