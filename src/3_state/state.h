/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:06 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "libft.h"
# include "stack.h"

typedef struct s_state
{
	t_stack	a;
	t_stack	b;
	t_buff	moves;
}	t_state;

bool	state_init(t_state *dst, uint *values, size_t values_size);
bool	state_dup(t_state *dst, const t_state *src);
void	state_free(t_state *state);

#endif
