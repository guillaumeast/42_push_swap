#include "chunk.h"
#include "sort_three.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>

// TODO [1]: Reduce chunk_size while A is getting smaller ?		=> edit chunk_update()

static bool	do_basic(t_state *state, t_config *config, t_chunk *chunk);
// static bool	do_lis(t_state *state, t_config *config, t_chunk *chunk, t_lis *lis);
static void	chunk_update(t_chunk *chunk);

bool	chunk(t_state *state, t_config *config)
{
	t_lis	lis;

	if (!config->lis)
	{
		while (state->a.len > 3 && !stack_is_sorted(&state->a))
		{
			if (!do_basic(state, config, &config->chunk))
				return (false);
		}
	}
	else
	{
		if (!lis_compute_best(&state->a, &lis))
			return (false);
		while (state->a.len > 3 && !stack_is_sorted(&state->a))
		{
			// TODO: lis version
			if (!do_basic(state, config, &config->chunk))
				return (lis_free(&lis), false);
		}
		lis_free(&lis);
	}
	return (sort_three(state, config));
}

static bool	do_basic(t_state *state, t_config *config, t_chunk *chunk)
{
	size_t	target_index;
	uint	target_value;

	target_index = 0;
	target_value = stack_get_value(&state->a, target_index);
	while (target_value < chunk->min || target_value > chunk->max)
		target_value = stack_get_value(&state->a, ++target_index);
	if (target_index <= state->a.len / 2)
	{
		if (!ra(&state->a, target_index, &state->moves))
			return (false);
	}
	else
		if (!rra(&state->a, state->a.len - target_index, &state->moves))
			return (false);
	if (!pb(&state->a, &state->b, 1, &state->moves))
		return (false);
	if (target_value < chunk->median)
		if (!rb(&state->b, 1, &state->moves))
			return (false);
	if (config->swap && !opti_swap_b(state, config))
		return (false);
	chunk_update(chunk);
	return (true);
}

static void	chunk_update(t_chunk *chunk)
{
	chunk->treated++;
	if (chunk->treated < chunk->size)
		return ;
	// cf TODO [1] at the top of the file
	chunk->treated = 0;
	chunk->min = chunk->max;
	chunk->max = chunk->min + chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
}
