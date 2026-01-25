#include "config.h"
#include "config_priv.h"
#include "naive.h"
#include "chunk.h"
#include "k_sort.h"
#include "greedy.h"
#include <stdlib.h>
#include <debug.h>	// TMP: remove before submit

static void	process_algos(t_config *config, uint raw_config);
static void	process_optis(t_config *config, uint raw_config);
static void	process_sizes(t_configs *configs, const size_t *sizes, size_t len);
static bool	process_lis(t_configs *configs, const t_state *state);

// Caller must free configs->data (and configs->lis and configs->lis_swap if configs->lis_set is true)
bool	config_init_list(t_configs *configs, const t_state *state)
{
	uint	*raw_configs;
	size_t	raw_configs_count;
	size_t	*chunk_sizes;
	size_t	chunk_sizes_count;
	size_t	i;

	fprintf(stderr, "ℹ️  Generating configs...\n");	// TMP: remove before submit
	if (!generate_raw_configs(&raw_configs, &raw_configs_count))
		return (false);
	if (!get_chunk_sizes(&chunk_sizes, &chunk_sizes_count, &state->a))
		return (free(raw_configs), false);
	configs->count = raw_configs_count * chunk_sizes_count;
	configs->data = malloc(configs->count * sizeof * configs->data);
	if (!configs->data)
		return (free(raw_configs), free(chunk_sizes), false);
	i = 0;
	configs->count = 0;
	while (i < raw_configs_count)
	{
		process_algos(&configs->data[configs->count], raw_configs[i]);
		process_optis(&configs->data[configs->count], raw_configs[i]);
		process_sizes(configs, chunk_sizes, chunk_sizes_count);
		i++;
	}
	if (!process_lis(configs, state))
		return (free(raw_configs), free(chunk_sizes), false);
	configs->lis_set = true;
	config_print_all(configs);	// TMP: remove before submit
	fprintf(stderr, "%s✅ %zu configs created%s\n\n", GREEN, configs->count, NC);	// TMP: remove before submit
	return (free(raw_configs), free(chunk_sizes), true);
}

static void process_algos(t_config *config, uint raw_config)
{
	if ((raw_config & ALGO_1_MASK) == NAIVE)
	{
		config->algo_1 = naive;
		config->algo_1_name = "NAIVE";
	}
	else if ((raw_config & ALGO_1_MASK) == CHUNK)
	{
		config->algo_1 = chunk;
		config->algo_1_name = "CHUNK";
	}
	else if ((raw_config & ALGO_1_MASK) == K_SORT)
	{
		config->algo_1 = k_sort;
		config->algo_1_name = "CHUNK";
	}
	if ((raw_config & ALGO_2_MASK) == GREEDY)
	{
		config->algo_2 = greedy;
		config->algo_2_name = "GREEDY";
	}
}

static void	process_optis(t_config *config, uint raw_config)
{
	uint	optis;

	optis = (raw_config & OPTI_MASK);
	config->opti_median = (optis & MEDIAN) != 0;
	config->opti_lis_swap = (optis & LIS_SWAP) != 0;
	config->opti_lis = config->opti_lis_swap || (optis & LIS) != 0;
	config->opti_swap_b = (optis & SWAP) != 0;
	// TMP: remove before submit (all following lines)
	if (config->opti_swap_b && config->opti_median && config->opti_lis_swap)
		config->opti_names = " + MEDIAN + LIS_SWAP + SWAP_B";
	else if (config->opti_swap_b && config->opti_median && config->opti_lis)
		config->opti_names = " + MEDIAN + LIS + SWAP_B";
	else if (config->opti_median && config->opti_lis_swap)
		config->opti_names = " + MEDIAN + LIS_SWAP";
	else if (config->opti_median && config->opti_lis)
		config->opti_names = " + MEDIAN + LIS";
	else if (config->opti_swap_b && config->opti_median)
		config->opti_names = " + MEDIAN + SWAP_B";
	else if (config->opti_swap_b && config->opti_lis_swap)
		config->opti_names = " + LIS_SWAP + SWAP_B";
	else if (config->opti_swap_b && config->opti_lis)
		config->opti_names = " + LIS + SWAP_B";
	else if (config->opti_median)
		config->opti_names = " + MEDIAN";
	else if (config->opti_lis_swap)
		config->opti_names = " + LIS_SWAP";
	else if (config->opti_lis)
		config->opti_names = " + LIS";
	else if (config->opti_swap_b)
		config->opti_names = " + SWAP_B";
	else
		config->opti_names = "";
}

static void	process_sizes(t_configs *configs, const size_t *sizes, size_t len)
{
	t_config	initial_config;
	size_t		i;

	initial_config = configs->data[configs->count];
	if (initial_config.algo_1 != chunk && initial_config.algo_1 != k_sort)
	{
		configs->count++;
		return ;
	}
	i = 0;
	while (i < len)
	{
		configs->data[configs->count] = initial_config;
		configs->data[configs->count].chunk_size = sizes[i];
		configs->count++;
		i++;
	}
}

static bool	process_lis(t_configs *configs, const t_state *state)
{
	size_t	i;

	if (!lis_compute_both(&state->a, &configs->lis, &configs->lis_swap))
		return (false);
	i = 0;
	while (i < configs->count)
	{
		if (configs->data[i].opti_lis_swap)
			configs->data[i].lis = configs->lis_swap;
		else if (configs->data[i].opti_lis)
			configs->data[i].lis = configs->lis;
		i++;
	}
	return (true);
}
