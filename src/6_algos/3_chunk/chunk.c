#include "chunk.h"
#include "sort_three.h"
#include "stack.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>
#include "debug.h"	// TMP: remove before submit

// TODO [1]: Reduce chunk_size while A is getting smaller (hill climbing ??) ?		=> edit update_chunk()

typedef struct s_chunk
{
	size_t	size;
	uint	min;
	uint	max;
	uint	median;
	size_t	treated;
}	t_chunk;

typedef struct s_target
{
	size_t	index;
	uint	val;
}	t_target;

static bool	find(t_state *st, const t_config *cfg, t_target *trg, t_chunk *chk);
static bool	go(t_state *state, const t_target *target);
static bool	exec(t_state *state, const t_config *cfg, uint val, t_chunk *chunk);
static void	update_chunk(t_chunk *chunk);

bool	chunk(t_state *state, const t_config *config)
{
	t_target	target;
	t_chunk		chunk;
	bool		is_sorted;

	chunk.size = config->chunk_size;
	chunk.min = 0;
	chunk.max = (uint)chunk.size;
	chunk.median = (chunk.min + chunk.max) / 2;
	chunk.treated = 0;
	is_sorted = stack_is_sorted(&state->a);
	while (state->a.len > 3 && !is_sorted)
	{
		if (!find(state, config, &target, &chunk))
			return (false);
		if (!go(state, &target))
			return (false);
		if (!exec(state, config, target.val, &chunk))
			return (false);
		is_sorted = stack_is_sorted(&state->a);
	}
	if (!is_sorted)
		return (sort_three(state, config));
	return (true);
}

static bool	find(t_state *st, const t_config *cfg, t_target *trg, t_chunk *chk)
{
	fprintf(stderr, "[🔦 DEBUG] Searching next trg (%u - %u)...\n", chk->min, chk->max);	// TODO: tmp debug
	trg->index = 0;
	while (true)
	{
		trg->val = stack_get_value(&st->a, (long)trg->index);
		if (cfg->opti_lis_swap && cfg->lis.swap[trg->val])
		{
			fprintf(stderr, "[🔦 DEBUG] ===> Swapping %u...\n", trg->val);		// TODO: tmp debug
			if (!go(st, trg))
				return (false);
			if (!opti_swap_lis(st, cfg, trg->val))
				return (false);
			fprintf(stderr, "[🔦 DEBUG] ===> Recalling find_next()...\n");		// TODO: tmp debug
			return (find(st, cfg, trg, chk));
		}
		if (trg->val < chk->min || trg->val > chk->max)
			break ;
		trg->index++;
	}
	fprintf(stderr, "[🔦 DEBUG] Target %u found!\n", trg->val);				// TODO: tmp debug
	return (true);
}

static bool	go(t_state *state, const t_target *target)
{
	fprintf(stderr, "[🔦 DEBUG] ======> Rotating to %u...\n", target->val);				// TODO: tmp debug
	if (target->index <= state->a.len / 2)
		return (ra(state, target->index));
	return (rra(state, state->a.len - target->index));
}

static bool	exec(t_state *state, const t_config *cfg, uint val, t_chunk *chunk)
{
	fprintf(stderr, "[🔦 DEBUG] =========> Processing %u...\n", val);						// TODO: tmp debug
	if (cfg->opti_lis && cfg->lis.keep[val])
		return (ra(state, 1));
	else
	{
		if (!pb(state, 1))
			return (false);
		if (cfg->opti_median && val < chunk->median)
			if (!rb(state, 1))
				return (false);
		if (cfg->opti_swap_b && !opti_swap_b(state, cfg))
			return (false);
	}
	update_chunk(chunk);
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
	chunk->max = chunk->min + (uint)chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
}
