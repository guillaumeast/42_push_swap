/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:53:36 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:53:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stack.h"

static inline void	extract_from(t_stack *stack, size_t count);

void	stack_rotate(t_stack *stack, size_t count)
{
	stack->offset = (stack->offset + count) % stack->len;
}

void	stack_reverse_rotate(t_stack *stack, size_t count)
{
	stack->offset = modulo((long)stack->offset - (long)count, stack->len);
}

void	stack_swap(t_stack *stack)
{
	size_t	next_index;
	uint	tmp;

	next_index = (stack->offset + 1) % stack->len;
	tmp = stack->data[stack->offset];
	stack->data[stack->offset] = stack->data[next_index];
	stack->data[next_index] = tmp;
}

void	stack_push(t_stack *from, t_stack *to, size_t count)
{
	uint	*dst_ptr;
	uint	*src_ptr;
	size_t	len_to_move;
	size_t	i;

	src_ptr = to->data + to->offset;
	dst_ptr = src_ptr + count;
	len_to_move = (to->len - to->offset) * sizeof * (to->data);
	ft_memmove(dst_ptr, src_ptr, len_to_move);
	i = 0;
	while (i < count)
	{
		to->data[to->offset + count - 1 - i] = from->data[from->offset + i];
		i++;
	}
	to->len += count;
	extract_from(from, count);
}

static inline void	extract_from(t_stack *stack, size_t count)
{
	uint	*dst_ptr;
	uint	*src_ptr;
	size_t	move_len;

	if (stack->offset + count == stack->len)
		stack->offset = 0;
	else if (stack->offset + count > stack->len)
	{
		dst_ptr = stack->data;
		src_ptr = stack->data + ((stack->offset + count) % stack->len);
		move_len = (stack->len - count) * sizeof * stack->data;
		ft_memmove(dst_ptr, src_ptr, move_len);
	}
	else
	{
		dst_ptr = stack->data + stack->offset;
		src_ptr = dst_ptr + count;
		move_len = (stack->len - stack->offset - count) * sizeof * stack->data;
		ft_memmove(dst_ptr, src_ptr, move_len);
	}
	stack->len -= count;
}
