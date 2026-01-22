#include "config.h"
#include "config_priv.h"
#include "naive.h"
#include "chunk.h"
#include "greedy.h"
#include <stdlib.h>
#include <debug.h>	// TMP: remove before submit

static void	process_algos(t_config *config, uint raw_config);
static void	process_optis(t_config *config, uint raw_config);
static void	process_chunks(t_chunk_list *chunks, t_config_list *configs);
static bool	process_lis(t_config_list *configs, t_state *state);

// Caller must free configs->data, configs->lis and configs->lis_swap
bool	config_init_list(t_config_list *configs, t_state *state)
{
	uint			*raw_list;
	size_t			raw_list_size;
	t_chunk_list	chunk_list;
	size_t	i;

	fprintf(stderr, "ℹ️  Generating configs...\n");	// TMP: remove before submit
	if (!generate_configs(&raw_list, &raw_list_size))
		return (false);
	if (!generate_chunks(&chunk_list, state->a.len))
		return (free(raw_list), false);
	configs->count = raw_list_size * chunk_list.count;
	configs->data = malloc(configs->count * sizeof * configs->data);
	if (!configs->data)
		return (free(raw_list), free(chunk_list.data), false);
	i = 0;
	configs->count = 0;
	while (i < raw_list_size)
	{
		process_algos(&configs->data[configs->count], raw_list[i]);
		process_optis(&configs->data[configs->count], raw_list[i]);
		process_chunks(&chunk_list, configs);
		i++;
	}
	if (!process_lis(configs, state))
		return (free(raw_list), free(chunk_list.data), false);
	config_print_all(configs);	// TMP: remove before submit
	fprintf(stderr, "\n");		// TMP: remove before submit
	return (free(raw_list), free(chunk_list.data), true);
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

static void	process_chunks(t_chunk_list *chunks, t_config_list *configs)
{
	size_t		chunk_i;
	t_config	initial_config;

	if (configs->data[configs->count].algo_1 == chunk)
	{
		initial_config = configs->data[configs->count];
		chunk_i = 0;
		while (chunk_i < chunks->count)
		{
			configs->data[configs->count] = initial_config;
			configs->data[configs->count].chunk = chunks->data[chunk_i];
			configs->count++;
			chunk_i++;
		}
	}
	else
		configs->count++;
}

static bool	process_lis(t_config_list *configs, t_state *state)
{
	size_t	i;

	if (!lis_compute_both(&state->a, &configs->lis, &configs->lis_swap))
		return (false);
	configs->lis_set = true;
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
