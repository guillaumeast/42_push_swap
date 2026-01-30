/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_PRIV_H
# define MOVES_PRIV_H

# include "libft.h"

typedef enum e_move
{
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SA,
	SB,
	SS,
	PA,
	PB,
	NO_OP
}	t_move;

bool	move_add(char move, size_t count, t_buff *list);

#endif
