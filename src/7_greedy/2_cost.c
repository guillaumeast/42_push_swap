/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cost.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:09:08 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:09:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "greedy_priv.h"

static void	compute_raw(t_choice *cost, size_t stack_len, size_t idx);
static void	compute_tot(const t_raw_cost *a, const t_raw_cost *b, t_total *res);

t_total	best_cost(const t_stack *a, size_t i_a, const t_stack *b, size_t i_b)
{
	t_choice	a_cost;
	t_choice	b_cost;
	t_total		best;
	t_total		current;

	compute_raw(&a_cost, a->len, i_a);
	compute_raw(&b_cost, b->len, i_b);
	compute_tot(&a_cost.opti, &b_cost.opti, &best);
	compute_tot(&a_cost.opti, &b_cost.bad, &current);
	if (current.total < best.total)
		best = current;
	compute_tot(&a_cost.bad, &b_cost.opti, &current);
	if (current.total < best.total)
		best = current;
	return (best);
}

static void	compute_raw(t_choice *cost, size_t stack_len, size_t idx)
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

static void	compute_tot(const t_raw_cost *a, const t_raw_cost *b, t_total *res)
{
	res->rr = (size_t)min((long)a->rotate, (long)b->rotate);
	res->rrr = (size_t)min((long)a->reverse, (long)b->reverse);
	res->ra = a->rotate - res->rr;
	res->rb = b->rotate - res->rr;
	res->rra = a->reverse - res->rrr;
	res->rrb = b->reverse - res->rrr;
	res->total = res->rr + res->rrr + res->ra + res->rb + res->rra + res->rrb;
}
