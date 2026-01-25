#include "swap.h"
#include "moves.h"
#include "lis.h"
// # include "debug.h"

// TODO: opti_swap_a()

bool	opti_swap_b(t_state *state, const t_config *config)
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
	if (!config->opti_lis_swap)	// NOTE: swapping A with LIS activated could broken A swaps computed by LIS module
	{
		first_value = stack_get_value(&state->a, 0);
		second_value = stack_get_value(&state->a, 1);
		third_value = stack_get_value(&state->a, 2);
		if (first_value > second_value && first_value < third_value)
			return (ss(state));	
	}
	return (sb(state));
}

// TODO: rename to opti_swap_a_lis()
bool	opti_swap_lis(t_state *state, t_config *config, uint value)
{
	uint 	first_value;
	uint 	second_value;

	if (!config->opti_lis_swap || !config->lis.swap[value])
		return (true);
	config->lis.swap[value] = false;
	// TODO: can conflict with opti_swap_b ! (disabled waiting for investigations)
	if (config->opti_swap_b || state->b.len < 2)
		return (sa(state));
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (first_value < second_value)
		return (ss(state));
	return (sa(state));
}
