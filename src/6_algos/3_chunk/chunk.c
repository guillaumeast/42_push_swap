#include "chunk.h"
#include "sort_three.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>
#include "debug.h"	// TMP: remove before submit

// TODO [1]: Reduce chunk_size while A is getting smaller ?		=> edit update_chunk()

typedef struct s_target
{
	size_t	index;
	uint	val;
}	t_target;

static bool	go_next(t_state *state, t_config *config, t_target *target);
static bool	do_step(t_state *state, t_config *config, uint value, t_lis *lis);
static void	update_chunk(t_chunk *chunk);

bool	chunk(t_state *state, t_config *config)
{
	t_target	target;
	t_lis		lis;

	if (config->opti_lis)
		lis = config->lis;
	else if (config->opti_lis_swap)
		lis = config->lis_swap;
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		if (!go_next(state, config, &target))
			return (false);
		if (!do_step(state, config, target.val, &lis))
			return (false);
		update_chunk(&config->chunk);
	}
	return (sort_three(state, config));
}

static bool	go_next(t_state *state, t_config *config, t_target *target)
{
	target->index = 0;
	target->val = stack_get_value(&state->a, target->index);
	fprintf(stderr, "\n[🔦 DEBUG] Searching next target...\n");					// TODO: tmp debug
	while (target->val < config->chunk.min || target->val > config->chunk.max)
		target->val = stack_get_value(&state->a, ++target->index);
	fprintf(stderr, "\n[🔦 DEBUG] Target found!\n");							// TODO: tmp debug
	if (target->index <= state->a.len / 2)
	{
		if (!ra(state, target->index))
			return (false);
	}
	else
		if (!rra(state, state->a.len - target->index))
			return (false);
	return (true);
}

static bool	do_step(t_state *state, t_config *config, uint value, t_lis *lis)
{
	if (config->opti_lis_swap && lis->swap[value])
		return (opti_swap_lis(state, lis, value));
	else if ((config->opti_lis || config->opti_lis_swap) && lis->keep[value])
		return (ra(state, 1));
	else
	{
		if (!pb(state, 1))
			return (false);
		if (value < config->chunk.median)
			if (!rb(state, 1))
				return (false);
		if (config->opti_swap_b && !opti_swap_b(state, config))
			return (false);
	}
	return (true);
}

static void	update_chunk(t_chunk *chunk)
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
