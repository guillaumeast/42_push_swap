/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:54:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	move_add(char move, size_t count, t_buff *list)
{
	while (count--)
	{
		if (!buff_append(list, &move, 1))
			return (false);
	}
	return (true);
}
