#include "naive.h"
#include "sort_three.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include "swap.h"

static bool	do_lis(t_state *state, t_config *config, t_median *med);
static bool	do_basic(t_state *state, t_config *config, t_median *med);

bool	naive(t_state *state, t_config *config)
{
	t_median	median;

	if (!config->opti_swap_b && !config->opti_median && !config->opti_lis)
	{
		if (!pb(state, state->a.len - 3))
			return (false);
		return (sort_three(state, config));
	}
	median.present = NULL;	// NOTE: in case of premature free from do_lis / do_basic() failure
	if (config->opti_median && !median_init(&median, state->a.len))
		return (false);
	if (config->opti_lis)
	{
		if (!do_lis(state, config, &median))
			return (median_free(&median), false);
	}
	else
		while (state->a.len > 3 && !stack_is_sorted(&state->a))
			if (!do_basic(state, config, &median))
				return (median_free(&median), false);
	if (config->opti_median)
		median_free(&median);
	return (sort_three(state, config));
}

static bool	do_lis(t_state *state, t_config *config, t_median *med)
{
	t_lis	lis;
	uint	current_value;

	if (config->opti_lis)
		lis = config->lis;
	else if (config->opti_lis_swap)
		lis = config->lis_swap;
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		current_value = stack_get_value(&state->a, 0);
		if (lis.swap[current_value])
		{
			if (!opti_swap_lis(state, &lis, current_value))
				return (false);
		}
		else if (lis.keep[current_value])
		{
			if (!ra(state, 1))
				return (false);
		}
		else
			if (!do_basic(state, config, med))
				return (false);
	}
	return (true);
}

static bool	do_basic(t_state *state, t_config *config, t_median *med)
{
	if (!pb(state, 1))
		return (false);
	if (config->opti_median)
		median_update(med, stack_get_value(&state->b, 0));
	if (config->opti_swap_b)
		if (!opti_swap_b(state, config))
			return (false);
	if (config->opti_median && stack_get_value(&state->b, 0) < med->median)
		if (!rb(state, 1))
			return (false);
	return (true);
}
