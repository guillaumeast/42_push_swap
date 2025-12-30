/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:04:16 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/30 17:10:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>

static t_lis	*lis_get(t_stack *stack, size_t start_index);
static t_lis	*lis_new(t_tail *tail, t_stack *stack);
static void		lis_compute_swaps(t_lis *lis, t_stack *stack, size_t index);

t_lis	*lis_get_best(t_stack *stack)
{
	size_t	start_index;
	t_lis	*tmp_lis;
	t_lis	*best_lis;
	size_t	max_len;

	best_lis = NULL;
	max_len = 0;
	start_index = 0;
	while (start_index < stack->count)
	{
		tmp_lis = lis_get(stack, start_index);
		if (!tmp_lis)
			continue ;
		else if (tmp_lis->final_len > max_len)
		{
			lis_free(&best_lis);
			best_lis = tmp_lis;
			max_len = best_lis->final_len;
		}
		else
			lis_free(&tmp_lis);
		start_index++;
	}
	return (best_lis);
}

static t_lis	*lis_get(t_stack *stack, size_t start_index)
{
	t_tail	*tail;
	t_lis	*lis;
	int		index;

	tail = tail_get(stack, start_index);
	if (!tail)
		return (NULL);
	lis = lis_new(tail, stack);
	if (!lis)
		return (tail_free(&tail), NULL);
	index = tail->pos[tail->max_len - 1];
	while (index != -1)
	{
		lis->keep[stack->values[index]] = true;
		lis->keep_count++;
		index = tail->prev[index];
	}
	index = 0;
	while (index < (int)stack->count)
	{
		lis_compute_swaps(lis, stack, (size_t)index);
		index++;
	}
	lis->final_len = lis->keep_count + lis->swap_count;
	return (lis);
}

static t_lis	*lis_new(t_tail *tail, t_stack *stack)
{
	t_lis	*lis;

	if (!tail || !stack)
		return (NULL);
	lis = malloc(sizeof * lis);
	if (!lis)
		return (NULL);
	lis->keep = malloc(stack->count * sizeof * lis->keep);
	lis->swap = malloc(stack->count * sizeof * lis->keep);
	if (!lis->keep || !lis->swap)
		return (lis_free(&lis), NULL);
	ft_memset(lis->keep, false, stack->count * sizeof * lis->keep);
	ft_memset(lis->swap, false, stack->count * sizeof * lis->swap);
	lis->keep_count = 0;
	lis->swap_count = 0;
	lis->final_len = 0;
	lis->start_index = tail->start_index;
	return (lis);
}

static void	lis_compute_swaps(t_lis *lis, t_stack *stack, size_t index)
{
	size_t	next_kept_i;
	int		current;
	int		next;
	int		second_next;

	current = stack->values[index];
	next = stack->values[(index + 1) % stack->count];
	if (lis->keep[current] || !lis->keep[next])
		return ;
	next_kept_i = (index + 2) % stack->count;
	while (next_kept_i != index && !lis->keep[stack->values[next_kept_i]])
		next_kept_i = (next_kept_i + 1) % stack->count;
	if (next_kept_i == index)
		return ;
	second_next = stack->values[next_kept_i];
	if (current > next && (current < second_next || second_next == 0))
	{
		lis->swap[current] = true;
		lis->swap_count++;
	}
}

void	lis_free(t_lis **lis)
{
	if (!lis || !*lis)
		return ;
	if ((*lis)->keep)
		free((*lis)->keep);
	if ((*lis)->swap)
		free((*lis)->swap);
	free(*lis);
	*lis = NULL;
}
