/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include "libft.h"
# include "state.h"

/* --- rotate.c --- */

bool	rr(t_state *state, size_t count);
bool	ra(t_state *state, size_t count);
bool	rb(t_state *state, size_t count);

/* --- rotate_reverse.c --- */

bool	rrr(t_state *state, size_t count);
bool	rra(t_state *state, size_t count);
bool	rrb(t_state *state, size_t count);

/* --- swap.c --- */

bool	ss(t_state *state);
bool	sa(t_state *state);
bool	sb(t_state *state);

/* --- push.c --- */

bool	pa(t_state *state, size_t count);
bool	pb(t_state *state, size_t count);

/* --- optimize/main.c --- */

void	optimize_moves(t_buff *moves);

/* --- print.c --- */

bool	moves_print(const t_buff *list);

#endif
