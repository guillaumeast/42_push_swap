#include "naive.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include <stdio.h>	// TODO: tmp debug

static bool	lis_push(t_state *state, t_config *config, t_median *med);
static bool	lis_swap(t_state *state, t_lis *lis, uint current_value);
static bool	basic_push(t_state *state, t_config *config, t_median *med);
static bool	basic_swap(t_state *state, t_config *config);

bool	naive(t_state *state, t_config *config)
{
	t_median	median;
	bool		res;

	if (!config->swap && !config->median && !config->lis)
		return (pb(&state->a, &state->b, state->a.len - 2, &state->moves));
	median.present = NULL;	// in case of premature free from basic_push failure
	if (config->median && !median_init(&median, state->a.len))
		return (false);
	if (config->lis)
		res = lis_push(state, config, &median);
	else
	{
		res = true;
		while (state->a.len > 2)
			if (!basic_push(state, config, &median))
				return (median_free(&median), false);
	}
	if (config->median)
		median_free(&median);
	return (res);
}

static bool	lis_push(t_state *state, t_config *config, t_median *med)
{
	t_lis	*lis;
	uint	current_value;

	lis = lis_get_best(&state->a);	// TODO: make it take a lis ptr and return a bool
	if (!lis)
		return (false);
	while (!stack_is_sorted(&state->a))	// Keep track of first kept/swapped value to stop the loop (to reduce compute complexity)
	{
		current_value = stack_get_value(&state->a, 0);
		if (lis->swap[current_value])
			lis_swap(state, lis, current_value);
		else if (lis->keep[current_value])
		{
			if (!ra(&state->a, 1, &state->moves))	// Make bulk rotates (to reduce compute complexity)
				return (false);
		}
		else
			if (!basic_push(state, config, med))
				return (false);
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
		if (!sa(&state->a, &state->moves))
			return (false);
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (state->b.len == 2 && first_value < second_value)
		if (!ss(&state->a, &state->b, &state->moves))
			return (false);
	third_value = stack_get_value(&state->b, 2);
	if (first_value < second_value && first_value > third_value)
		if (!ss(&state->a, &state->b, &state->moves))
			return (false);
	if (!sa(&state->a, &state->moves))
		return (false);
	return (true);
}

static bool	basic_push(t_state *state, t_config *config, t_median *med)
{
	if (!pb(&state->a, &state->b, 1, &state->moves))
		return (false);
	if (config->median)
		median_update(med, stack_get_value(&state->b, 0));
	if (config->swap)
		if (!basic_swap(state, config))
			return (false);
	if (config->median && stack_get_value(&state->b, 0) < med->median)
		if (!rb(&state->b, 1, &state->moves))
			return (false);
	return (true);
}

// TODO: add a lis_update() function to recompute new_indexes ?! (check if they can be inserted between previous keeped value and next keep value)
static bool	basic_swap(t_state *state, t_config *config)
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
	if (!config->lis)	// swapping A with LIS activated could broken A swaps computed by LIS module
	{
		first_value = stack_get_value(&state->a, 0);
		second_value = stack_get_value(&state->a, 1);
		third_value = stack_get_value(&state->a, 2);
		if (first_value > second_value && first_value < third_value)
			return (ss(&state->a, &state->b, &state->moves));	
	}
	return (sb(&state->b, &state->moves));
}
