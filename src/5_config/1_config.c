#include "config.h"
#include "config_priv.h"
#include "naive.h"
#include "chunk.h"
#include "greedy.h"
#include <stdlib.h>
#include <debug.h>	// TMP: remove before submit

static void	process_algos(t_config *config, uint raw_config);
static void	process_optis(t_config *config, uint raw_config);
static void	process_chunks(t_chunk_list *chunks, t_config_list *configs, size_t *i);

// Caller must free configs->data
bool	config_init_list(t_config_list *configs, size_t values_count)
{
	uint			*raw_list;
	size_t			raw_list_size;
	t_chunk_list	chunk_list;
	size_t	i;

	fprintf(stderr, "ℹ️  Generating configs...\n");	// TMP: remove before submit
	raw_list = generate_configs(&raw_list_size);
	if (!raw_list)
		return (false);
	if (!chunk_generate(&chunk_list, values_count))
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
		process_chunks(&chunk_list, configs, &configs->count);
		i++;
	}
	fprintf(stderr, "\n");	// TMP: remove before submit
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
	uint		optis;

	optis = (raw_config & OPTI_MASK);
	config->swap = (optis & SWAP) != 0;
	config->median = (optis & MEDIAN) != 0;
	config->lis = (optis & LIS) != 0;
	if (config->swap && config->median && config->lis)
		config->opti_names = " + MEDIAN + LIS + SWAP";
	else if (config->swap && config->median)
		config->opti_names = " + MEDIAN + SWAP";
	else if (config->swap && config->lis)
		config->opti_names = " + LIS + SWAP";
	else if (config->median && config->lis)
		config->opti_names = " + MEDIAN + LIS";
	else if (config->swap)
		config->opti_names = " + SWAP";
	else if (config->median)
		config->opti_names = " + MEDIAN";
	else if (config->lis)
		config->opti_names = " + LIS";
	else
		config->opti_names = "";
}

static void	process_chunks(t_chunk_list *chunks, t_config_list *configs, size_t *i)
{
	size_t		chunk_i;
	t_config	initial_config;

	if (configs->data[*i].algo_1 == chunk)
	{
		initial_config = configs->data[*i];
		chunk_i = 0;
		while (chunk_i < chunks->count)
		{
			configs->data[*i] = initial_config;
			configs->data[*i].chunk = chunks->data[chunk_i];
			config_print(&configs->data[*i], *i, true);	// TMP: remove before submit
			(*i)++;
			chunk_i++;
		}
	}
	else
		(*i)++;
}
