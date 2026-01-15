#include "libft.h"
#include "moves.h"
#include "greedy.h"
#include "greedy_priv.h"

static t_insert	get_next_insert(t_stack *from, t_stack *to);

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
		current.cost = get_best_cost(to, current.target_index, from, i);
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
