#include "naive.h"
#include "sort_three.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include "swap.h"

static bool	push_to_b(t_state *state, const t_config *config, t_median *median);

bool	naive(t_state *state, const t_config *config)
{
	t_median	median;
	
	if (!config->opti_swap_b && !config->opti_median && !config->opti_lis)
		return (pb(state, state->a.len - 3) && sort_three(state, config));
	// NOTE: NULL in case of premature free when push_to_b() fails
	median.present = NULL;
	if (config->opti_median && !median_init(&median, state->a.len))
		return (false);
	if (!push_to_b(state, config, &median))
		return (median_free(&median), false);
	if (config->opti_median)
		median_free(&median);
	return (sort_three(state, config));
}

static bool	push_to_b(t_state *state, const t_config *config, t_median *median)
{
	uint	value;

	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		value = stack_get_value(&state->a, 0);
		if (config->opti_lis_swap && config->lis.swap[value])
			return (opti_swap_lis(state, config, value) && ra(state, 2));
		else if (config->opti_lis && config->lis.keep[value])
			return (ra(state, 1));
		else if (!pb(state, 1))
			return (false);
		if (config->opti_median && !opti_median(state, median, value))
			return (false);
		if (config->opti_swap_b && !opti_swap_b(state, config))
			return (false);
	}
	return (true);
}
