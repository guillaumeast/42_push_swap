/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:02:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimize_priv.h"

void	pattern_init(t_pattern *dst, t_move a, t_move b, t_move cumul)
{
	dst->a_move = a;
	dst->b_move = b;
	dst->cumul_move = cumul;
	dst->a_count = 0;
	dst->b_count = 0;
	dst->cumul_count = 0;
	dst->cumulnew = 0;
	dst->no_op_count = 0;
}

void	set_move(t_move *dst, t_buff *moves, long index)
{
	if (index < 0 || index >= (long)moves->len)
		*dst = NO_OP;
	else
		*dst = (t_move)moves->data[index];
}
