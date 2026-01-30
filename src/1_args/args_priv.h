/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_priv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:52:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:52:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_PRIV_H
# define ARGS_PRIV_H

# include <sys/types.h>

typedef struct s_sort_data
{
	int		*array;
	int		*tmp;
}	t_sort_data;

uint	*normalize(int *array, size_t size);

#endif
