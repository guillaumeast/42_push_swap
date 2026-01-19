#include "chunk.h"
#include "sort_three.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>

// TODO [1]: Reduce chunk_size while A is getting smaller ?		=> edit chunk_update()

typedef struct s_target
{
	size_t	index;
	uint	val;
}	t_target;

static bool	do_step(t_state *state, t_config *config, uint value, t_lis *lis);
static void	chunk_update(t_chunk *chunk);

bool	chunk(t_state *state, t_config *config)
{
	t_target	target;
	t_lis		lis;

	if (config->lis && !lis_compute_best(&state->a, &lis))
		return (false);
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		target.index = 0;
		target.val = stack_get_value(&state->a, target.index);
		while (target.val < config->chunk.min || target.val > config->chunk.max)
			target.val = stack_get_value(&state->a, ++target.index);
		if (target.index <= state->a.len / 2)
		{
			if (!ra(&state->a, target.index, &state->moves))
				return (false);
		}
		else
			if (!rra(&state->a, state->a.len - target.index, &state->moves))
				return (false);
		if (!do_step(state, config, target.val, &lis))
			return (false);
	}
	if (config->lis)
		lis_free(&lis);
	return (sort_three(state, config));
}

static bool	do_step(t_state *state, t_config *config, uint value, t_lis *lis)
{
	if (config->lis && lis->swap[value])
	{
		if (!opti_swap_lis(state, lis, value))
			return (false);
	}
	else if (config->lis && lis->keep[value])
	{
		if (!ra(&state->a, 1, &state->moves))
			return (false);
	}
	else
	{
		if (!pb(&state->a, &state->b, 1, &state->moves))
			return (false);
		if (value < config->chunk.median)
			if (!rb(&state->b, 1, &state->moves))
				return (false);
		if (config->swap && !opti_swap_b(state, config))
			return (false);
	}
	chunk_update(&config->chunk);
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
