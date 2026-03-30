/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_sort_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:04:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/04 23:17:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef K_SORT_PRIV_H
# define K_SORT_PRIV_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_window
{
	size_t		size;
	uint		min;
	uint		max;
	uint		treated_count;
}	t_window;

typedef struct s_target
{
	size_t	index;
	uint	value;
}	t_target;

#endif
