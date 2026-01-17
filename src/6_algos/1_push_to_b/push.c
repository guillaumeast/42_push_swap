#include "push.h"
#include "moves.h"

static bool		should_swap(t_stack *stack);

bool	push_to_b(t_config *config)
{
	if (!config)
		return (pb(&config->a, &config->b, config->a.len - 2, &config->moves));
	while (config->a.len > 2)
	{
		if (!pb(&config->a, &config->b, 1, &config->moves))
			return (false);
		if (config->swap && should_swap(&config->b))
			if (!sb(&config->b, &config->moves))
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
