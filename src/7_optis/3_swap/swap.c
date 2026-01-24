#include "swap.h"
#include "moves.h"
#include "lis.h"

bool	opti_swap_b(t_state *state, const t_config *config)
{
	uint	first_value;
	uint	second_value;

	if (state->b.len < 2)
		return (true);
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (state->b.len == 2 && first_value > second_value)
		return (true);
	if (!config->opti_lis_swap)	// NOTE: swapping A with LIS activated could broken A swaps computed by LIS module
	{
		first_value = stack_get_value(&state->a, 0);
		second_value = stack_get_value(&state->a, 1);
		if (first_value > second_value)
			return (ss(state));	
	}
	return (sb(state));
}

bool	opti_swap_lis(t_state *state, const t_config *config, uint value)
{
	uint 	first_value;
	uint 	second_value;

	config->lis.swap[value] = false;
	if (state->b.len < 2)
		return (sa(state));
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (first_value < second_value)
		return (ss(state));
	return (sa(state));
}
