#include "naive.h"
#include "sort_three.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include "swap.h"

static bool	lis_push(t_state *state, t_config *config, t_median *med);
static bool	lis_swap(t_state *state, t_lis *lis, uint current_value);
static bool	naive_push(t_state *state, t_config *config, t_median *med);

bool	naive(t_state *state, t_config *config)
{
	t_median	median;

	if (!config->swap && !config->median && !config->lis)
	{
		if (!pb(&state->a, &state->b, state->a.len - 3, &state->moves))
			return (false);
		return (sort_three(state, config));
	}
	median.present = NULL;	// NOTE: in case of premature free from lis_push / naive_push() failure
	if (config->median && !median_init(&median, state->a.len))
		return (false);
	if (config->lis)
	{
		if (!lis_push(state, config, &median))
			return (median_free(&median), false);
	}
	else
		while (state->a.len > 3)
			if (!naive_push(state, config, &median))
				return (median_free(&median), false);
	if (config->median)
		median_free(&median);
	return (sort_three(state, config));
}

static bool	lis_push(t_state *state, t_config *config, t_median *med)
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
			if (!lis_swap(state, &lis, current_value))
				return (lis_free(&lis), false);
		}
		else if (lis.keep[current_value])
		{
			if (!ra(&state->a, 1, &state->moves))
				return (lis_free(&lis), false);
		}
		else
			if (!naive_push(state, config, med))
				return (lis_free(&lis), false);
	}
	lis_free(&lis);
	return (true);
}

static bool	lis_swap(t_state *state, t_lis *lis, uint current_value)
{
	uint 	first_value;
	uint 	second_value;
	uint 	third_value;

	lis->swap[current_value] = false;
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

static bool	naive_push(t_state *state, t_config *config, t_median *med)
{
	if (!pb(&state->a, &state->b, 1, &state->moves))
		return (false);
	if (config->median)
		median_update(med, stack_get_value(&state->b, 0));
	if (config->swap)
		if (!opti_swap(state, config))
			return (false);
	if (config->median && stack_get_value(&state->b, 0) < med->median)
		if (!rb(&state->b, 1, &state->moves))
			return (false);
	return (true);
}
