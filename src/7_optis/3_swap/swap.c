#include "swap.h"
#include "moves.h"
#include "lis.h"

bool	opti_swap_b(t_state *state, t_config *config)
{
	uint	first_value;
	uint	second_value;

	if (state->b.len < 2)
		return (true);
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (state->b.len == 2 && first_value > second_value)
		return (true);
	if (!config->lis)	// NOTE: swapping A with LIS activated could broken A swaps computed by LIS module
	{
		first_value = stack_get_value(&state->a, 0);
		second_value = stack_get_value(&state->a, 1);
		if (first_value > second_value)
			return (ss(&state->a, &state->b, &state->moves));	
	}
	return (sb(&state->b, &state->moves));
}

bool	opti_swap_lis(t_state *state, t_lis *lis, uint current_value)
{
	uint 	first_value;
	uint 	second_value;
	uint 	third_value;

	lis->swap[current_value] = false;
	lis->keep[current_value] = true;
	if (state->b.len < 2)
		return (sa(&state->a, &state->moves));
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (state->b.len == 2 && first_value < second_value)
		return (ss(&state->a, &state->b, &state->moves));
	else if (state->b.len > 2)
	{
		third_value = stack_get_value(&state->b, 2);
		if (first_value < second_value && first_value > third_value)
			return (ss(&state->a, &state->b, &state->moves));
	}
	return (sa(&state->a, &state->moves));
}
