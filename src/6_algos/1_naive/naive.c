#include "naive.h"
#include "moves.h"

static bool		should_swap(t_stack *stack);

bool	naive(t_state *state, t_config *config)
{
	if (!config->swap)
		return (pb(&state->a, &state->b, state->a.len - 2, &state->moves));
	while (state->a.len > 2)
	{
		if (!pb(&state->a, &state->b, 1, &state->moves))
			return (false);
		if (should_swap(&state->b))
			if (!sb(&state->b, &state->moves))
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
