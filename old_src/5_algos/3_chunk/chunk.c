#include "chunk.h"
#include "sort_three.h"
#include "stack.h"
#include "moves.h"
#include "lis.h"
#include "swap.h"
#include <stdlib.h>

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
	// stack_print_line(&state->a, NULL, YELLOW);
	// fprintf(stderr, "\n");
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		if (!find(state, &cfg, &target, &chunk))
			return (config_free(&cfg), free(chunk.treated), false);
		if (!go(state, &target))
			return (config_free(&cfg), free(chunk.treated), false);
		if (!exec(state, &cfg, target.val, &chunk))
			return (config_free(&cfg), free(chunk.treated), false);
		// stack_print_line(&state->a, NULL, YELLOW);
		// fprintf(stderr, "\n");
	}
	config_free(&cfg);
	free(chunk.treated);
	return (sort_three(state, config));
}

static bool	find(t_state *st, const t_config *cfg, t_target *trg, t_chunk *chk)
{
	// fprintf(stderr, "%sSearching next target (%u - %u)...%s\n", GREY, chk->min, chk->max, NC);	// TODO: tmp debug
	trg->index = 0;
	while (true)
	{
		trg->val = stack_get_value(&st->a, (long)trg->index);
		if (cfg->opti_lis_swap && cfg->lis.swap[trg->val])		// [???] Si la valeur doit être swapped
			break ;
		if (trg->val >= chk->min && trg->val < chk->max)		// [???] Si la valeur fait partie du chunk
			break ;												// [NON] => on la traite normalement
		trg->index++;
		if (trg->index >= st->a.len)
		{
			// fprintf(stderr, "%s🚨 Target NOT found!%s\n", RED, NC);				// TODO: tmp debug
			return (false);
		}
	}
	// fprintf(stderr, "%s%u%s targeted!\n", YELLOW, trg->val, NC);				// TODO: tmp debug
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
		// fprintf(stderr, "%s%u %sopti_swap_lis()%s\n", YELLOW, val, BLUE, NC);				// TODO: tmp debug
		if (!opti_swap_lis(state, cfg, val))
			return (false);
	}
	if (cfg->opti_lis && cfg->lis.keep[val])
	{
		// fprintf(stderr, "%s%u %sra()%s\n", YELLOW, val, GREEN, NC);				// TODO: tmp debug
		if (!ra(state, 1))
			return (false);
	}
	else
	{
		// fprintf(stderr, "%s%u %spb()%s\n", YELLOW, val, RED, NC);				// TODO: tmp debug
		if (!pb(state, 1))
			return (false);
		if (cfg->opti_median && val < chunk->median)
		{
			// fprintf(stderr, "%s%u %srb()%s\n", YELLOW, val, BLUE, NC);				// TODO: tmp debug
			if (!rb(state, 1))
				return (false);
		}
		if (cfg->opti_swap_b)
		{
			// fprintf(stderr, "%s%u %sopti_swap_b()%s\n", YELLOW, val, BLUE, NC);				// TODO: tmp debug
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
	if (value < chunk->min || value >= chunk->max)
	{
		// fprintf(stderr, "%s%u%s outside chunk boundaries (%u - %u): skipping update%s\n", YELLOW, value, RED, chunk->min, chunk->max, NC);
		return ;
	}
	// if (chunk->treated[value])
	// {
	// 	fprintf(stderr, "%streated (%zu) => (array_disabled)%s\n", GREY, chunk->treated_count, NC);
	// 	// print_array_u(chunk->treated, chunk->treated_count, GREY, YELLOW, value, true);
	// 	fprintf(stderr, "%s%u%s already treated: skipping update%s\n", YELLOW, value, RED, NC);
	// 	exit(EXIT_FAILURE);
	// 	// return ;
	// }
	chunk->treated[value] = true;
	chunk->treated_count++;
	if (chunk->treated_count < chunk->size)
	{
		// fprintf(stderr, "%s%u%s treated: chunk is now %u - %u (%zu / %zu)%s\n", YELLOW, value, BLUE, chunk->min, chunk->max, chunk->treated_count, chunk->size, NC);
		return ;
	}
	// cf TODO [1] at the top of the file
	chunk->treated_count = 0;
	chunk->min = chunk->max;
	chunk->max = chunk->min + (uint)chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
	// fprintf(stderr, "%s%u%s treated: chunk is now %u - %u (%zu / %zu)%s\n", YELLOW, value, GREEN, chunk->min, chunk->max, chunk->treated_count, chunk->size, NC);
}
