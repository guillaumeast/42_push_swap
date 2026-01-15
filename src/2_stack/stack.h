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
bool	stack_dup(t_stack *dst, t_stack *src);
uint	stack_get_value(t_stack *stack, size_t index);
size_t	stack_get_target_index(t_stack *s, uint value);
bool	stack_is_sorted(t_stack *stack);
void	stack_print(t_stack *a, t_stack *b);	// TODO: tmp debug

#endif
