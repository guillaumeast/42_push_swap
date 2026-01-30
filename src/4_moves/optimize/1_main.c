/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:54:49 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:18:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "optimize_priv.h"

static void	prune_no_ops(t_buff *moves);
static void	move_data(t_buff *moves, size_t *write_index, size_t start_index);

void	optimize_moves(t_buff *moves)
{
	size_t	prev_len;

	while (true)
	{
		prev_len = moves->len;
		prune_all(moves);
		merge_all(moves);
		prune_no_ops(moves);
		if (moves->len >= prev_len)
			break ;
	}
}

static void	prune_no_ops(t_buff *moves)
{
	size_t	write_index;
	size_t	start_index;
	size_t	final_len;

	write_index = 0;
	start_index = 0;
	final_len = moves->len;
	while (write_index < moves->len && moves->data[write_index] != NO_OP)
		write_index++;
	while (write_index < moves->len)
	{
		start_index = write_index;
		while (start_index < moves->len && moves->data[start_index] == NO_OP)
			start_index++;
		if (start_index >= moves->len)
			break ;
		move_data(moves, &write_index, start_index);
		final_len = write_index;
	}
	while (final_len > 0 && moves->data[final_len - 1] == NO_OP)
		final_len--;
	if (final_len >= moves->len)
		return ;
	moves->len = final_len;
}

static void	move_data(t_buff *moves, size_t *write_index, size_t start_index)
{
	size_t	len;

	len = 1;
	while (start_index + len < moves->len
		&& moves->data[start_index + len] != NO_OP)
		len++;
	ft_memmove(moves->data + *write_index, moves->data + start_index, len);
	ft_memset(moves->data + *write_index + len,
		(int)NO_OP, start_index - *write_index);
	*write_index += len;
}
