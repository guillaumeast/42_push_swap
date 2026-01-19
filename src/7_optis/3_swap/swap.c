#include "swap.h"
#include "moves.h"

// TODO[1]: does it really make sens to NOT swap when first_value < third_value ??

bool	opti_swap(t_state *state, t_config *config)
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
		if (first_value > second_value || first_value < third_value)	// cf TODO[1] at the top of the file
			return (true);
	}
	if (!config->lis)	// NOTE: swapping A with LIS activated could broken A swaps computed by LIS module
	{
		first_value = stack_get_value(&state->a, 0);
		second_value = stack_get_value(&state->a, 1);
		third_value = stack_get_value(&state->a, 2);
		if (first_value > second_value && first_value < third_value)
			return (ss(&state->a, &state->b, &state->moves));	
	}
	return (sb(&state->b, &state->moves));
}
