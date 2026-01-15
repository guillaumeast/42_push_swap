#include "libft.h"
#include "stack.h"
#include "moves.h"

static bool	get_target_index(t_stack *stack, size_t *ret);

bool finish(t_stack *a, t_buff *move_list)
{
	size_t	target_index;

	if (!get_target_index(a, &target_index))
		return (false);
	if (target_index <= a->len / 2)
	{
		// TODO: switch commented parts for submit / debug
		// if (!ra(a, target_index, move_list))
		// 	return (false);
		if (!move_add(RA, target_index, move_list))
			return (false);
	}
	else
	{
		// TODO: switch commented parts for submit / debug
		// if (!rra(a, a->len - target_index, move_list))
		// 	return (false);
		if (!move_add(RRA, a->len - target_index, move_list))
			return (false);
	}
	return (true);
}

static bool	get_target_index(t_stack *stack, size_t *ret)
{
	size_t	i;

	i = 0;
	while (i < stack->len)
	{
		if (stack->data[i] == 0)
		{
			*ret = modulo((long)i - (long)stack->offset, stack->len);
			return (true);
		}
		i++;
	}
	return (false);
}
