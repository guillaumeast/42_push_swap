#include "libft.h"
#include "stack.h"
#include <stdlib.h>

static void	set_index(t_stack_index *dst, t_stack_index *src);

bool	stack_init(t_stack *stack, int *values, size_t count)
{
	if (!values)
	{
		stack->values = malloc(count * sizeof *stack->values);
		if (!stack->values)
			return (false);
		ft_memset(stack->values, EMPTY_CELL, count * sizeof *stack->values);
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
	t_stack_index	i;

	i.real = (int)stack->offset;
	i.virtual = 0;
	while (i.virtual < (int)index)
	{
		i.real = (i.real + 1) % (int)stack->cap;
		if (stack->values[i.real] != EMPTY_CELL)
			i.virtual++;
	}
	return (stack->values[i.real]);
}

// TODO: refacto SANS SINGERIE 🦧
int		stack_get_target_index(t_stack *s, int value)
{
	t_stack_index	i;
	t_stack_index	target;
	t_stack_index	smallest;

	i.real = (int)s->offset;
	1 && (i.virtual = 0, target.real = -1, smallest.real = -1);
	while (i.virtual < (int)s->len)
	{
		if (s->values[i.real] != EMPTY_CELL)
		{
			if (smallest.real == -1 
				|| s->values[i.real] <= s->values[smallest.real])
				set_index(&smallest, &i);
			if (s->values[i.real] > value && (target.real == -1 
				|| s->values[i.real] <= s->values[target.real]))
				set_index(&target, &i);
			i.virtual++;
		}
		i.real = (i.real + 1) % (int)s->cap;
	}
	if (target.real != -1)
		return (target.virtual);
	return (smallest.virtual);
}

static void	set_index(t_stack_index *dst, t_stack_index *src)
{
	dst->real = src->real;
	dst->virtual = src->virtual;
}

bool	stack_is_sorted(t_stack *stack)
{
	size_t	i;
	size_t	breaks;
	int		last_value;

	if (stack->len <= 2)
		return (true);
	breaks = 0;
	i = 0;
	while (stack->values[i] == EMPTY_CELL)
		i++;
	last_value = stack->values[i];
	while (++i < stack->cap)
	{
		if (stack->values[i] == EMPTY_CELL)
			continue ;
		else if (stack->values[i] < last_value)
			breaks++;
		if (breaks > 1)
			return (false);
		last_value = stack->values[i];
	}
	return (true);
}
