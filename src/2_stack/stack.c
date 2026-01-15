#include "libft.h"
#include "stack.h"
#include <stdlib.h>

bool	stack_init(t_stack *a, t_stack *b, uint *values, size_t count)
{
	a->data = values;
	a->offset = 0;
	a->len = count;
	a->cap = count;
	b->data = malloc(count * sizeof * b->data);
	if (!b->data)
		return (false);
	b->offset = 0;
	b->len = 0;
	b->cap = 0;
	return (true);
}

bool	stack_dup(t_stack *dst, t_stack *src)
{
	dst->data = malloc(src->cap * sizeof * dst->data);
	if (!dst->data)
		return (false);
	ft_memcpy(dst->data, src->data, src->len * sizeof * src->data);
	dst->offset = src->offset;
	dst->len = src->len;
	dst->cap = src->cap;
	return (true);
}

uint	stack_get_value(t_stack *stack, size_t index)
{
	return (stack->data[(stack->offset + index) % stack->len]);
}

uint	stack_get_target_index(t_stack *s, uint value)
{
	size_t	i;
	int		target_i;
	uint	target_v;
	int		smallest_i;
	uint	smallest_v;

	i = 0;
	target_i = -1;
	smallest_i = -1;
	while (i < s->len)
	{
		if (smallest_i == -1 || s->data[i] <= smallest_v)
		{
			smallest_i = (int)i;
			smallest_v = s->data[i];
		}
		if (s->data[i] > value && (target_i == -1 || s->data[i] <= target_v))
		{
			target_i = (int)i;
			target_v = s->data[i];
		}
		i++;
	}
	if (target_i != -1)
		return ((uint)(((size_t)target_i + s->offset) % s->len));
	return ((uint)(((size_t)smallest_i + s->offset) % s->len));
}

bool	stack_is_sorted(t_stack *stack)
{
	size_t	i;
	size_t	breaks;
	uint	last_value;

	if (stack->len <= 2)
		return (true);
	breaks = 0;
	i = 0;
	last_value = stack->data[i];
	while (++i < stack->len && breaks < 2)
	{
		if (stack->data[i] < last_value)
			breaks++;
		last_value = stack->data[i];
	}
	return (breaks < 2);
}
