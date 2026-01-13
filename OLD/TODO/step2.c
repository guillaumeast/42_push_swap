/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:03:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 20:50:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static t_move	*get_next_move(t_stack *a, t_stack *b);
static size_t	get_target_index(t_stack *a, int b_value);
static void		compute_cost(t_move *mv, t_stack *a, t_stack *b);
static void		execute_move(t_move *move, t_stack *a, t_stack *b);

bool	step_2(t_stack *a, t_stack *b)
{
	t_move	*move;

	while (b->count > 0)
	{
		move = get_next_move(a, b);
		if (!move)
			return (false);
		execute_move(move, a, b);
		free(move);
	}
	return (true);
}

// static t_move	*get_next_move(t_stack *a, t_stack *b)
// {
// 	size_t	i;
// 	t_move	*tmp_move;
// 	t_move	*best_move;

// 	best_move = NULL;
// 	i = 0;
// 	while (i < b->count)
// 	{
// 		tmp_move = malloc(sizeof * tmp_move);
// 		if (!tmp_move)
// 			return (free(best_move), NULL);
// 		tmp_move->b_index = i;
// 		tmp_move->a_target_index = get_target_index(a, b->values[i]);
// 		compute_cost(tmp_move, a, b);
// 		if (!best_move || tmp_move->total_cost < best_move->total_cost)
// 		{
// 			free(best_move);
// 			best_move = tmp_move;
// 		}
// 		else
// 			free(tmp_move);
// 		i++;
// 	}
// 	return (best_move);
// }

// static size_t	get_target_index(t_stack *a, int b_value)
// {
// 	size_t	i;
// 	int		target_index;
// 	int		smallest_index;

// 	target_index = -1;
// 	smallest_index = -1;
// 	i = 0;
// 	while (i < a->count)
// 	{
// 		if (smallest_index == -1 || a->values[i] <= a->values[smallest_index])
// 			smallest_index = (int)i;
// 		if (a->values[i] > b_value
// 			&& (target_index == -1 || a->values[i] <= a->values[target_index]))
// 			target_index = (int)i;
// 		i++;
// 	}
// 	if (target_index != -1)
// 		return ((size_t)target_index);
// 	return ((size_t)smallest_index);
// }

// static void	compute_cost(t_move *mv, t_stack *a, t_stack *b)
// {
// 	mv->ra = 0;
// 	mv->rra = 0;
// 	if (mv->a_target_index <= a->count / 2)
// 		mv->ra = mv->a_target_index;
// 	else
// 		mv->rra = a->count - mv->a_target_index;
// 	mv->rb = 0;
// 	mv->rrb = 0;
// 	if (mv->b_index <= b->count / 2)
// 		mv->rb = mv->b_index;
// 	else
// 		mv->rrb = b->count - mv->b_index;
// 	mv->rr = (size_t)ft_min((int)mv->ra, (int)mv->rb);
// 	mv->rrr = (size_t)ft_min((int)mv->rra, (int)mv->rrb);
// 	mv->ra = mv->ra - mv->rr;
// 	mv->rb = mv->rb - mv->rr;
// 	mv->rra = mv->rra - mv->rrr;
// 	mv->rrb = mv->rrb - mv->rrr;
// 	mv->total_cost = mv->ra + mv->rb + mv->rr + mv->rra + mv->rrb + mv->rrr;
// }

// static void	execute_move(t_move *move, t_stack *a, t_stack *b)
// {
// 	while (move->ra-- > 0)
// 		rotate(a, b, A);
// 	while (move->rb-- > 0)
// 		rotate(a, b, B);
// 	while (move->rr-- > 0)
// 		rotate(a, b, BOTH);
// 	while (move->rra-- > 0)
// 		rotate_reverse(a, b, A);
// 	while (move->rrb-- > 0)
// 		rotate_reverse(a, b, B);
// 	while (move->rrr-- > 0)
// 		rotate_reverse(a, b, BOTH);
// 	push(a, b, A);
// }
