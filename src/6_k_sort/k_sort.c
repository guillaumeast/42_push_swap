/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:04:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/04 23:41:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "k_sort_priv.h"
#include "moves.h"
#include <stdlib.h>

static void	find(t_state *state, t_window *window, t_target *ret_target);
static bool	rotate(t_state *state, size_t index);
static bool	exec(t_state *state, t_window *window, uint value);
static void	update_window(t_window *window, size_t stack_len);

bool	k_sort(t_state *state)
{
	t_window	window;
	t_target	target;

	window.size = state->a.len / 6;
	window.min = 0;
	window.treated_count = 0;
	window.max = (uint)window.size;
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		find(state, &window, &target);
		if (!rotate(state, target.index))
			return (false);
		if (!exec(state, &window, target.value))
			return (false);
		update_window(&window, state->a.len);
	}
	return (true);
}

static void	find(t_state *state, t_window *window, t_target *ret_target)
{
	size_t	index;
	uint	value;

	index = 0;
	value = stack_get_value(&state->a, 0);
	while (value < window->min || value >= window->max)
		value = stack_get_value(&state->a, (long)++index);
	ret_target->index = index;
	ret_target->value = value;
}

static bool	rotate(t_state *state, size_t index)
{
	if (index <= state->a.len / 2)
		return (ra(state, index));
	return (rra(state, state->a.len - index));
}

static bool	exec(t_state *state, t_window *window, uint value)
{
	if (!pb(state, 1))
		return (false);
	if (value < window->treated_count)
		return (rb(state, 1));
	return (true);
}

static void	update_window(t_window *window, size_t stack_len)
{
	window->treated_count++;
	(void)stack_len;
	// if (window->size > stack_len / 5 && window->size > 1)
	// {
	// 	window->size = window->size * 6 / 7;
	// 	window->max = window->treated_count + (uint)window->size;
	// }
	// else
		window->max++;
}
