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
	uint	*treated;
	size_t	treated_count;
}	t_chunk;

typedef struct s_target
{
	size_t	index;
	uint	val;
}	t_target;

static bool	find(t_state *st, const t_config *cfg, t_target *trg, t_chunk *chk);
static bool	go(t_state *state, const t_target *target);
static bool	exec(t_state *state, t_config *cfg, uint val, t_chunk *chunk);
static void	update_chunk(t_chunk *chunk, uint value);

bool	chunk(t_state *state, const t_config *config)
{
	t_target	target;
	t_chunk		chunk;
	t_config	cfg;

	if (!config_dup(&cfg, config, state->a.len))
		return (false);
	chunk.treated = malloc(state->a.len * sizeof * chunk.treated);
	if (!chunk.treated)
		return (config_free(&cfg), false);
	ft_memset(chunk.treated, false, state->a.len * sizeof * chunk.treated);
	chunk.size = config->chunk_size;
	chunk.min = 0;
	chunk.max = (uint)chunk.size;
	chunk.median = (chunk.min + chunk.max) / 2;
	chunk.treated_count = 0;
	// fprintf(stderr, "Initial => ");
	// stack_print_line(&state->a, NULL, YELLOW);
	// fprintf(stderr, "\n");
	while (!stack_is_sorted(&state->a))
	{
		if (!find(state, &cfg, &target, &chunk))
			return (config_free(&cfg), free(chunk.treated), false);
		if (!go(state, &target))
			return (config_free(&cfg), free(chunk.treated), false);
		if (!exec(state, &cfg, target.val, &chunk))
			return (config_free(&cfg), free(chunk.treated), false);
		// fprintf(stderr, "After   => ");
		// stack_print_line(&state->a, NULL, YELLOW);
		// fprintf(stderr, "\n");
	}
	config_free(&cfg);
	free(chunk.treated);
	return (sort_three(state, config));
}

static bool	find(t_state *st, const t_config *cfg, t_target *trg, t_chunk *chk)
{
	// fprintf(stderr, "[🔦 DEBUG] Searching next target (%u - %u)...\n", chk->min, chk->max);	// TODO: tmp debug
	trg->index = 0;
	while (true)
	{
		trg->val = stack_get_value(&st->a, (long)trg->index);
		if (cfg->opti_lis_swap && cfg->lis.swap[trg->val])
			break ;
		if (trg->val >= chk->min && trg->val <= chk->max)
			break ;
		trg->index++;
		if (trg->index >= st->a.len)
		{
			// fprintf(stderr, "%s🚨 Target NOT found!%s\n", RED, NC);				// TODO: tmp debug
			return (false);
		}
	}
	// fprintf(stderr, "[🔦 DEBUG] Target %u found!\n", trg->val);				// TODO: tmp debug
	return (true);
}

static bool	go(t_state *state, const t_target *target)
{
	// fprintf(stderr, "[🔦 DEBUG] Rotating to %u...\n", target->val);				// TODO: tmp debug
	if (target->index <= state->a.len / 2)
		return (ra(state, target->index));
	return (rra(state, state->a.len - target->index));
}

static bool	exec(t_state *state, t_config *cfg, uint val, t_chunk *chunk)
{
	// fprintf(stderr, "[🔦 DEBUG] Processing %u...\n", val);						// TODO: tmp debug
	if (cfg->opti_lis_swap && cfg->lis.swap[val])
	{
		// fprintf(stderr, "[🔦 DEBUG] Calling opti_swap_lis()...\n");				// TODO: tmp debug
		if (!opti_swap_lis(state, cfg, val))
			return (false);
	}
	if (cfg->opti_lis && cfg->lis.keep[val])
	{
		// fprintf(stderr, "[🔦 DEBUG] Calling ra()...\n");				// TODO: tmp debug
		if (!ra(state, 1))
			return (false);
	}
	else
	{
		// fprintf(stderr, "[🔦 DEBUG] Calling pb()...\n");				// TODO: tmp debug
		if (!pb(state, 1))
			return (false);
		if (cfg->opti_median && val < chunk->median)
		{
			// fprintf(stderr, "[🔦 DEBUG] Calling rb()...\n");				// TODO: tmp debug
			if (!rb(state, 1))
				return (false);
		}
		if (cfg->opti_swap_b)
		{
			// fprintf(stderr, "[🔦 DEBUG] Calling opti_swap_b()...\n");				// TODO: tmp debug
			if (!opti_swap_b(state, cfg))
				return (false);
		}
	}
	// fprintf(stderr, "[🔦 DEBUG] Updating chunk...\n");				// TODO: tmp debug
	update_chunk(chunk, val);
	return (true);
}

static void	update_chunk(t_chunk *chunk, uint value)
{
	if (value < chunk->min || value > chunk->max)
		return ;
	if (chunk->treated[value])
		return ;
	chunk->treated[value] = true;
	chunk->treated_count++;
	if (chunk->treated_count < chunk->size)
		return ;
	// cf TODO [1] at the top of the file
	chunk->treated_count = 0;
	chunk->min = chunk->max;
	chunk->max = chunk->min + (uint)chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
}
