/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	rr(t_state *state, size_t count)
{
	stack_rotate(&state->a, count);
	stack_rotate(&state->b, count);
	return (move_add(RR, count, &state->moves));
}

bool	ra(t_state *state, size_t count)
{
	if (state->a.len < 2)
		return (true);
	stack_rotate(&state->a, count);
	return (move_add(RA, count, &state->moves));
}

bool	rb(t_state *state, size_t count)
{
	if (state->b.len < 2)
		return (true);
	stack_rotate(&state->b, count);
	return (move_add(RB, count, &state->moves));
}
