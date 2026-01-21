#include "chunk.h"
#include "sort_three.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>
#include "debug.h"	// TMP: remove before submit

// TODO [1]: Reduce chunk_size while A is getting smaller (hill climbing ??) ?		=> edit update_chunk()

typedef struct s_target
{
	size_t	index;
	uint	val;
}	t_target;

static bool	find_next(t_state *state, t_config *config, t_target *target);
static bool	go_next(t_state *state, t_target *target);
static bool	do_step(t_state *state, t_config *config, uint value);
static void	update_chunk(t_chunk *chunk);

bool	chunk(t_state *state, t_config *config)
{
	t_target	target;

	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		if (!find_next(state, config, &target))
			return (false);
		if (!go_next(state, &target))
			return (false);
		if (!do_step(state, config, target.val))
			return (false);
	}
	return (sort_three(state, config));
}

static bool	find_next(t_state *state, t_config *config, t_target *target)
{
	fprintf(stderr, "[🔦 DEBUG] Searching next target (%u - %u)...\n", config->chunk.min, config->chunk.max);	// TODO: tmp debug
	target->index = 0;
	while (true)
	{
		target->val = stack_get_value(&state->a, target->index);
		if (config->opti_lis_swap && config->lis.swap[target->val])
		{
			fprintf(stderr, "[🔦 DEBUG] ===> Swapping %u...\n", target->val);		// TODO: tmp debug
			if (!go_next(state, target))
				return (false);
			if (!opti_swap_lis(state, config, target->val))
				return (false);
			fprintf(stderr, "[🔦 DEBUG] ===> Recalling find_next()...\n");		// TODO: tmp debug
			return (find_next(state, config, target));
		}
		if (target->val < config->chunk.min || target->val > config->chunk.max)
			break ;
		target->index++;
	}
	fprintf(stderr, "[🔦 DEBUG] Target %u found!\n", target->val);				// TODO: tmp debug
	return (true);
}

static bool	go_next(t_state *state, t_target *target)
{
	fprintf(stderr, "[🔦 DEBUG] ======> Rotating to %u...\n", target->val);				// TODO: tmp debug
	if (target->index <= state->a.len / 2)
		return (ra(state, target->index));
	return (rra(state, state->a.len - target->index));
}

static bool	do_step(t_state *state, t_config *config, uint value)
{
	fprintf(stderr, "[🔦 DEBUG] =========> Processing %u...\n", value);						// TODO: tmp debug
	if (config->opti_lis && config->lis.keep[value])
		return (ra(state, 1));
	else
	{
		if (!pb(state, 1))
			return (false);
		if (config->opti_median && value < config->chunk.median)
			if (!rb(state, 1))
				return (false);
		if (config->opti_swap_b && !opti_swap_b(state, config))
			return (false);
	}
	update_chunk(&config->chunk);
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
