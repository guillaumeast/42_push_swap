#include "libft.h"
#include "stack.h"
#include <stdlib.h>

// Caller must free stack->data
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
	b->cap = count;
	return (true);
}

bool	stack_dup(t_stack *dst, const t_stack *src)
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

uint	stack_get_value(const t_stack *stack, long index)
{
	size_t	i;

	i = modulo((long)stack->offset + index, stack->len);
	return (stack->data[i]);
}

size_t	stack_get_target_index(const t_stack *s, uint value)
{
	size_t	i;
	long	target_i;
	uint	target_v;
	long	smallest_i;
	uint	smallest_v;

	1 && (i = 0, target_i = -1, smallest_i = -1);
	while (i < s->len)
	{
		if (smallest_i == -1 || s->data[i] <= smallest_v)
		{
			smallest_i = (long)i;
			smallest_v = s->data[i];
		}
		if (s->data[i] > value && (target_i == -1 || s->data[i] <= target_v))
		{
			target_i = (long)i;
			target_v = s->data[i];
		}
		i++;
	}
	if (target_i != -1)
		return (modulo(target_i - (long)s->offset, s->len));
	return (modulo(smallest_i - (long)s->offset, s->len));
}

bool	stack_is_sorted(const t_stack *stack)
{
	size_t	i;
	size_t	breaks;
	uint	previous_value;

	if (stack->len <= 2)
		return (true);
	breaks = 0;
	i = 0;
	previous_value = stack->data[stack->len - 1];
	while (i < stack->len && breaks < 2)
	{
		if (stack->data[i] < previous_value)
			breaks++;
		previous_value = stack->data[i];
		i++;
	}
	return (breaks < 2);
}
