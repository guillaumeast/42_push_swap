/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:53:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:53:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

typedef struct s_stack
{
	uint	*data;
	size_t	offset;
	size_t	len;
	size_t	cap;
}	t_stack;

bool	stack_init(t_stack *a, t_stack *b, uint *values, size_t count);
bool	stack_dup(t_stack *dst, const t_stack *src);
uint	stack_get_value(const t_stack *stack, long index);
size_t	stack_get_target_index(const t_stack *s, uint value);
bool	stack_is_sorted(const t_stack *stack);

#endif
