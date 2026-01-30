/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_greedy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:08:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:08:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "moves.h"
#include "greedy.h"
#include "greedy_priv.h"

static t_insert	get_next_insert(const t_stack *from, const t_stack *to);

bool	greedy(t_state *state)
{
	t_insert	next_insertion;

	while (state->b.len > 0)
	{
		next_insertion = get_next_insert(&state->b, &state->a);
		if (!rr(state, next_insertion.cost.rr))
			return (false);
		if (!ra(state, next_insertion.cost.ra))
			return (false);
		if (!rb(state, next_insertion.cost.rb))
			return (false);
		if (!rrr(state, next_insertion.cost.rrr))
			return (false);
		if (!rra(state, next_insertion.cost.rra))
			return (false);
		if (!rrb(state, next_insertion.cost.rrb))
			return (false);
		if (!pa(state, 1))
			return (false);
	}
	return (true);
}

static t_insert	get_next_insert(const t_stack *from, const t_stack *to)
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
		current_value = stack_get_value(from, (long)i);
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
