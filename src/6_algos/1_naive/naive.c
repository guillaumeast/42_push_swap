#include "naive.h"
#include "moves.h"
#include "median.h"

static bool	should_swap(t_stack *stack);

// TODO: implement LIS opti (swap rotate and push following LIS decision)

// bool moyenne
// bool lis_no_swap
// bool lis_swap

bool	naive(t_state *state, t_config *config)
{
	t_median	median;

	if (!config->swap && !config->median)
		return (pb(&state->a, &state->b, state->a.len - 2, &state->moves));
	if (config->median && !median_init(&median, state->a.len))
		return (false);
	while (state->a.len > 2)
	{
		if (!pb(&state->a, &state->b, 1, &state->moves))
			return (false);
		if (config->median)
			median_update(&median, stack_get_value(&state->b, 0));
		if (config->swap && should_swap(&state->b))
			if (!sb(&state->b, &state->moves))
				return (false);
		if (stack_get_value(&state->b, 0) < median.median)
			if (!rb(&state->b, 1, &state->moves))
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
