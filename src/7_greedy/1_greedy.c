/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_greedy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:08:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/04 23:48:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "moves.h"
#include "greedy.h"
#include "greedy_priv.h"

static t_insert	get_next_insert(const t_stack *from, const t_stack *to);
t_total	best_cost(const t_stack *a, size_t i_a, const t_stack *b, size_t i_b);
static void	raw_cost(t_choice *cost, size_t stack_len, size_t idx);
static void	total_cost(const t_raw_cost *a, const t_raw_cost *b, t_total *res);

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

	ft_bzero(&best, sizeof best);
	1 && (best_is_set = false, i = 0);
	while (i < from->len)
	{
		ft_bzero(&current, sizeof current);
		current.from_index = i;
		current.from_value = stack_get_value(from, (long)i);
		current.target_index = stack_get_target_index(to, current.from_value);
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

t_total	best_cost(const t_stack *a, size_t i_a, const t_stack *b, size_t i_b)
{
	t_choice	a_cost;
	t_choice	b_cost;
	t_total		best;
	t_total		current;

	raw_cost(&a_cost, a->len, i_a);
	raw_cost(&b_cost, b->len, i_b);
	total_cost(&a_cost.opti, &b_cost.opti, &best);
	total_cost(&a_cost.opti, &b_cost.bad, &current);
	if (current.total < best.total)
		best = current;
	total_cost(&a_cost.bad, &b_cost.opti, &current);
	if (current.total < best.total)
		best = current;
	return (best);
}

static void	raw_cost(t_choice *cost, size_t stack_len, size_t idx)
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

static void	total_cost(const t_raw_cost *a, const t_raw_cost *b, t_total *res)
{
	res->rr = (size_t)min((long)a->rotate, (long)b->rotate);
	res->rrr = (size_t)min((long)a->reverse, (long)b->reverse);
	res->ra = a->rotate - res->rr;
	res->rb = b->rotate - res->rr;
	res->rra = a->reverse - res->rrr;
	res->rrb = b->reverse - res->rrr;
	res->total = res->rr + res->rrr + res->ra + res->rb + res->rra + res->rrb;
}
