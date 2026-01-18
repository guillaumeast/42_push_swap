#include "config.h"
#include "config_priv.h"
#include "naive.h"
#include "greedy.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

static t_config	*config_convert(uint raw_config);
static void		process_opti_names(t_config *config);

t_config	**config_get_list(void)
{
	uint		*raw_list;
	size_t		raw_list_size;
	t_config	**final_list;
	size_t		i;

	raw_list = generate_configs(&raw_list_size);
	if (!raw_list)
		return (NULL);
	final_list = malloc((raw_list_size + 1) * sizeof * final_list);
	if (!final_list)
		return (free(raw_list), NULL);
	i = 0;
	fprintf(stderr, "ℹ️  Generating configs...\n");
	while (i < raw_list_size)
	{
		final_list[i] = config_convert(raw_list[i]);
		if (!final_list[i])
			return (free(raw_list), config_list_free(&final_list), NULL);
		config_print(final_list[i], i, true);
		i++;
	}
	fprintf(stderr, "\n");
	final_list[i] = NULL;
	free(raw_list);
	return (final_list);
}

static t_config	*config_convert(uint raw_config)
{
	t_config	*res;
	uint		optis;

	res = malloc(sizeof * res);
	if (!res)
		return (NULL);
	if ((raw_config & ALGO_1_MASK) == NAIVE)
	{
		res->algo_1 = naive;
		res->algo_1_name = "NAIVE";
	}
	if ((raw_config & ALGO_2_MASK) == GREEDY)
	{
		res->algo_2 = greedy;
		res->algo_2_name = "GREEDY";
	}
	res->opti_names = "";
	optis = (raw_config & OPTI_MASK);
	res->swap = (optis & SWAP) != 0;
	res->median = (optis & MEDIAN) != 0;
	res->lis = (optis & LIS) != 0;
	process_opti_names(res);
	return (res);
}

static void	process_opti_names(t_config *config)
{
	if (config->swap && config->median && config->lis)
		config->opti_names = "+ SWAP + MEDIAN + LIS";
	else if (config->swap && config->median)
		config->opti_names = "+ SWAP + MEDIAN";
	else if (config->swap && config->lis)
		config->opti_names = "+ SWAP + LIS";
	else if (config->median && config->lis)
		config->opti_names = "+ MEDIAN + LIS";
	else if (config->swap)
		config->opti_names = "+ SWAP ";
	else if (config->median)
		config->opti_names = "+ MEDIAN ";
	else if (config->lis)
		config->opti_names = "+ LIS ";
}

void	config_list_free(t_config ***config_list)
{
	size_t	i;

	i = 0;
	while ((*config_list)[i])
	{
		free((*config_list)[i]);
		i++;
	}
	free(*config_list);
	*config_list = NULL;
}

// TODO: tmp debug
# include "config_priv.h"
void	config_print_all(t_config **configs)
{
	size_t	i;

	i = 0;
	while(configs[i])
	{
		config_print(configs[i], i, true);
		i++;
	}
}

void	config_print(t_config *config, size_t index, bool print_index)
{
	if (print_index)
		fprintf(stderr, "⚙️  CONFIG[%zu] => ", index);
	fprintf(stderr, "%s + %s %s\n", config->algo_1_name, config->algo_2_name, config->opti_names);
}
