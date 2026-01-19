#include "libft.h"
#include "chunk.h"
#include "chunk_private.h"
#include "sort_three.h"
#include "moves.h"
#include "swap.h"

# include <stdio.h>
// TODO [1]: Include chunk_size into config to automaticaly test several values		=> edit chunk_init()
// TODO [2]: Reduce chunk_size while A is getting smaller ?							=> edit chunk_update()

static void	chunk_init(t_chunk *chunk, size_t values_count);
static void	chunk_update(t_chunk *chunk);
static bool	chunk_push(t_state *state, t_config *config, t_chunk *chunk);

bool	chunk(t_state *state, t_config *config)
{
	t_chunk		chunk;

	chunk_init(&chunk, state->a.len);
	while (state->a.len > 3)
	{
		if (!chunk_push(state, config, &chunk))
			return (false);
	}
	return (sort_three(state, config));
}

static void	chunk_init(t_chunk *chunk, size_t values_count)
{
	// cf TODO [1] at the top of the file
	// chunk->size = 5 * (uint)square_root_rounded((int)values_count);
	// chunk->size = 8 * (uint)square_root_rounded((int)values_count);
	chunk->size = (uint)values_count / 3;
	chunk->min = 0;
	chunk->max = chunk->min + chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
	chunk->treated = 0;
}

static void	chunk_update(t_chunk *chunk)
{
	chunk->treated++;
	if (chunk->treated < chunk->size)
		return ;
	// cf TODO [2] at the top of the file
	chunk->treated = 0;
	chunk->min = chunk->max;
	chunk->max = chunk->min + chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
}

static bool	chunk_push(t_state *state, t_config *config, t_chunk *chunk)
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
	if (config->swap && !opti_swap(state, config))
		return (false);
	chunk_update(chunk);
	return (true);
}

