#include "push.h"
#include "moves.h"

static bool		should_swap(t_stack *stack);

bool	push_to_b(t_stack *a, t_stack *b, t_push_opti *opti, t_buff *list)
{
	if (!opti)
		return (pb(a, b, a->len - 2, list));
	while (a->len > 2)
	{
		if (!pb(a, b, 1, list))
			return (false);
		if (opti->swap && should_swap(b))
			if (!sb(b, list))
				return (false);
	}
	return (true);
}

static bool	should_swap(t_stack *stack)
{
	uint	first_value;
	uint	second_value;
	uint	third_value;

	if (stack->len < 2)
		return (false);
	first_value = stack_get_value(stack, 0);
	second_value = stack_get_value(stack, 1);
	if (stack->len == 2)
		return (first_value < second_value);
	third_value = stack_get_value(stack, 2);
	return (first_value < second_value && first_value > third_value);
}
