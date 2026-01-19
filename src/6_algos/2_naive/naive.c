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

	if (!config->swap && !config->median && !config->lis)
	{
		if (!pb(&state->a, &state->b, state->a.len - 3, &state->moves))
			return (false);
		return (sort_three(state, config));
	}
	median.present = NULL;	// NOTE: in case of premature free from do_lis / do_basic() failure
	if (config->median && !median_init(&median, state->a.len))
		return (false);
	if (config->lis)
	{
		if (!do_lis(state, config, &median))
			return (median_free(&median), false);
	}
	else
		while (state->a.len > 3 && !stack_is_sorted(&state->a))
			if (!do_basic(state, config, &median))
				return (median_free(&median), false);
	if (config->median)
		median_free(&median);
	return (sort_three(state, config));
}

static bool	do_lis(t_state *state, t_config *config, t_median *med)
{
	t_lis	lis;
	uint	current_value;

	if (!lis_compute_best(&state->a, &lis))
		return (false);
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		current_value = stack_get_value(&state->a, 0);
		if (lis.swap[current_value])
		{
			if (!opti_swap_lis(state, &lis, current_value))
				return (lis_free(&lis), false);
		}
		else if (lis.keep[current_value])
		{
			if (!ra(&state->a, 1, &state->moves))
				return (lis_free(&lis), false);
		}
		else
			if (!do_basic(state, config, med))
				return (lis_free(&lis), false);
	}
	lis_free(&lis);
	return (true);
}

static bool	do_basic(t_state *state, t_config *config, t_median *med)
{
	if (!pb(&state->a, &state->b, 1, &state->moves))
		return (false);
	if (config->median)
		median_update(med, stack_get_value(&state->b, 0));
	if (config->swap)
		if (!opti_swap_b(state, config))
			return (false);
	if (config->median && stack_get_value(&state->b, 0) < med->median)
		if (!rb(&state->b, 1, &state->moves))
			return (false);
	return (true);
}
