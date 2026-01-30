/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:53:39 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:53:40 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_OPS_H
# define STACK_OPS_H

# include "stack.h"

void	stack_rotate(t_stack *stack, size_t count);
void	stack_reverse_rotate(t_stack *stack, size_t count);
void	stack_swap(t_stack *stack);
void	stack_push(t_stack *from, t_stack *to, size_t count);

#endif
