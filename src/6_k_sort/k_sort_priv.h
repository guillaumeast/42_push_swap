/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:04:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:07:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef K_SORT_PRIV_H
# define K_SORT_PRIV_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_window
{
	size_t		size;
	size_t		capacity;
	uint		min;
	uint		med;
	uint		max;
	bool		*treated;
	size_t		treated_count;
}	t_window;

typedef struct s_target
{
	size_t	index;
	uint	value;
}	t_target;

bool	window_init(t_window *window, size_t capacity, size_t size);
void	window_update(t_window *window, uint value, size_t stack_len);
void	window_free(t_window *window);

#endif
