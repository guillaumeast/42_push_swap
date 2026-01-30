/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	ss(t_state *state)
{
	stack_swap(&state->a);
	stack_swap(&state->b);
	return (move_add(SS, 1, &state->moves));
}

bool	sa(t_state *state)
{
	if (state->a.len < 2)
		return (true);
	stack_swap(&state->a);
	return (move_add(SA, 1, &state->moves));
}

bool	sb(t_state *state)
{
	if (state->b.len < 2)
		return (true);
	stack_swap(&state->b);
	return (move_add(SB, 1, &state->moves));
}
