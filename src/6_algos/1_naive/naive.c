#include "naive.h"
#include "moves.h"
#include "median.h"

static bool	swap(t_state *state);

// TODO: lis_no_swap
// TODO: lis_swap

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
		if (config->swap)
			if (!swap(state))
				return (false);
		if (config->median && stack_get_value(&state->b, 0) < median.median)
			if (!rb(&state->b, 1, &state->moves))
				return (false);
	}
	if (config->median)
		median_free(&median);
	return (true);
}

// TODO: also swap A if possible
static bool	swap(t_state *state)
{
	uint	first_value;
	uint	second_value;
	uint	third_value;

	if (state->b.len < 2)
		return (true);
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (state->b.len == 2 && first_value > second_value)
		return (true);
	else
	{
		third_value = stack_get_value(&state->b, 2);
		if (first_value > second_value || first_value < third_value)
			return (true);
	}
	// TODO: add a lis_update() functionto recompute new_indexes (check if they can be inserted between previous keeped value and next keep value)
	first_value = stack_get_value(&state->a, 0);
	second_value = stack_get_value(&state->a, 1);
	third_value = stack_get_value(&state->a, 2);
	if (first_value > second_value && first_value < third_value)
		return (ss(&state->a, &state->b, &state->moves));
	return (sb(&state->b, &state->moves));
}
