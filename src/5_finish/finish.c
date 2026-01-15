#include "libft.h"
#include "stack.h"

static bool	get_target_index(t_stack *stack, size_t *ret);

bool finish(t_stack *a, t_buff *move_list)
{
	char	move_as_char;
	size_t	move_count;
	size_t	target_index;

	if (!get_target_index(a, &target_index))
		return (false);
	if (target_index <= a->len / 2)
	{
		move_as_char = RA;
		move_count = target_index;
	}
	else
	{
		move_as_char = RRA;
		move_count = a->len - target_index;
	}
	while (move_count-- > 0)
	{
		stack_rotate(a, NULL, A, move_as_char == RRA);
		if (!buff_append(move_list, &move_as_char, 1))
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
