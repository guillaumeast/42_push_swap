#include "libft.h"
#include "moves.h"
#include "greedy.h"
#include "greedy_priv.h"

static t_insert	get_next_insert(t_stack *from, t_stack *to);

bool	greedy(t_state *state, t_config *config)
{
	t_insert	next_insertion;

	(void)config;
	while (state->b.len > 0)
	{
		next_insertion = get_next_insert(&state->b, &state->a);
		if (!rr(&state->a, &state->b, next_insertion.cost.rr, &state->moves))
			return (false);
		if (!ra(&state->a, next_insertion.cost.ra, &state->moves))
			return (false);
		if (!rb(&state->b, next_insertion.cost.rb, &state->moves))
			return (false);
		if (!rrr(&state->a, &state->b, next_insertion.cost.rrr, &state->moves))
			return (false);
		if (!rra(&state->a, next_insertion.cost.rra, &state->moves))
			return (false);
		if (!rrb(&state->b, next_insertion.cost.rrb, &state->moves))
			return (false);
		if (!pa(&state->a, &state->b, 1, &state->moves))
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
