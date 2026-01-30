#ifndef STACK_OPS_H
# define STACK_OPS_H

# include "stack.h"

void	stack_rotate(t_stack *stack, size_t count);
void	stack_reverse_rotate(t_stack *stack, size_t count);
void	stack_swap(t_stack *stack);
void	stack_push(t_stack *from, t_stack *to, size_t count);

#endif
