/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"
#include "moves_priv.h"
#include <unistd.h>

static bool	add_to_buffer(t_buff *dst, t_move move);

bool	moves_print(const t_buff *list)
{
	size_t	i;
	t_move	move;
	t_buff	printable;

	if (!buff_init(&printable, list->len * 4))
		return (false);
	i = 0;
	while (i < list->len)
	{
		move = (t_move)list->data[i++];
		if (!add_to_buffer(&printable, move))
			return (buff_free(&printable), false);
	}
	write(1, printable.data, printable.len);
	buff_free(&printable);
	return (true);
}

static bool	add_to_buffer(t_buff *dst, t_move move)
{
	if (move == RR)
		return (buff_append(dst, "rr\n", 3));
	else if (move == RRR)
		return (buff_append(dst, "rrr\n", 4));
	else if (move == RA)
		return (buff_append(dst, "ra\n", 3));
	else if (move == RB)
		return (buff_append(dst, "rb\n", 3));
	else if (move == RRA)
		return (buff_append(dst, "rra\n", 4));
	else if (move == RRB)
		return (buff_append(dst, "rrb\n", 4));
	else if (move == SS)
		return (buff_append(dst, "ss\n", 3));
	else if (move == SA)
		return (buff_append(dst, "sa\n", 3));
	else if (move == SB)
		return (buff_append(dst, "sb\n", 3));
	else if (move == PA)
		return (buff_append(dst, "pa\n", 3));
	else if (move == PB)
		return (buff_append(dst, "pb\n", 3));
	else if (move == NO_OP)
		return (true);
	return (false);
}
