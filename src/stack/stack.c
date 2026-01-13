#include "libft.h"
#include "stack.h"
#include <stdlib.h>

bool	stack_init(t_stack *stack, int *values, size_t count)
{
	if (!values)
	{
		stack->values = malloc(count * sizeof *stack->values);
		if (!stack->values)
			return (false);
		ft_memset(stack->values, -1, count * sizeof *stack->values);
		stack->cap = count;
		stack->len = 0;
		stack->offset = 0;
	}
	else
	{
		stack->values = values;
		stack->cap = count;
		stack->len = count;
		stack->offset = 0;
	}
	return (true);
}

bool	stack_dup(t_stack *dst, t_stack *src)
{
	dst->values = malloc(src->cap * sizeof * dst->values);
	if (!dst->values)
		return (false);
	ft_memcpy(dst->values, src->values, src->cap * sizeof * src->values);
	dst->offset = src->offset;
	dst->cap = src->cap;
	dst->len = src->len;
	return (true);
}

int		stack_get_value(t_stack *stack, size_t index)
{
	size_t	real_index;
	size_t	virtual_index;

	real_index = stack->offset;
	virtual_index = 0;
	while (virtual_index < index)
	{
		if (stack->values[real_index] != -1)
			virtual_index++;
		real_index = (real_index + 1) % stack->cap;
	}
	return (stack->values[real_index]);
}

bool	stack_is_sorted(t_stack *stack)
{
	size_t	i;
	size_t	breaks;
	int		last_value;

	if (stack->len == 0)
		return (false);
	breaks = 0;
	i = 0;
	while (stack->values[i] == -1)
		i++;
	last_value = stack->values[i];
	while (++i < stack->cap)
	{
		if (stack->values[i] == -1)
			continue ;
		else if (stack->values[i] < last_value)
			breaks++;
		if (breaks > 1)
			return (false);
		last_value = stack->values[i];
	}
	return (true);
}
