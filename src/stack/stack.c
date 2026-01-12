#include "libft.h"
#include "stack.h"
#include <stdlib.h>

t_stack	stack_new(int *values, size_t offset, size_t count, size_t len)
{
	t_stack	stack;

	stack.values = values;
	stack.offset = offset;
	stack.cap = count;
	stack.len = len;
	return (stack);
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
