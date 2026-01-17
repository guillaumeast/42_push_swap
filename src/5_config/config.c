#include "config.h"
#include "config_priv.h"
#include <stdlib.h>

static t_config	*config_convert(uint raw_config);

t_config	**config_get_list(void)
{
	uint		*raw_list;
	size_t		raw_list_size;
	t_config	**final_list;
	size_t		i;

	raw_list = generate_configs(&raw_list_size);
	if (!raw_list)
		return (NULL);
	final_list = malloc(raw_list_size * sizeof * final_list);
	if (!final_list)
		return (free(raw_list), NULL);
	i = 0;
	while (i < raw_list_size)
	{
		final_list[i] = config_convert(raw_list[i]);
		if (!final_list[i])
			return (free(raw_list), config_list_free(&final_list), NULL);
		config_print(final_list[i]);	// TODO: tmp debug
		i++;
	}
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
	res->algo_1 = (raw_config & ALGO_1_MASK);
	res->algo_2 = (raw_config & ALGO_2_MASK);
	optis = (raw_config & OPTI_MASK);
	res->swap = (optis & SWAP) != 0;
	return (res);
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
# include <stdio.h>
# include "config_priv.h"
void	config_print_all(t_config **configs)
{
	while(*configs)
	{
		config_print(*configs);
		configs++;
	}
}

void	config_print(t_config *config)
{
	printf("------ CONFIG ------ \n");
	if (config->algo_1 == NAIVE)
		printf("-> algo_1 = NAIVE\n");
	else if (config->algo_1 == LIS)
		printf("-> algo_1 = LIS\n");
	else if (config->algo_1 == CHUNK)
		printf("-> algo_1 = CHUNK\n");
	else if (config->algo_1 == K_SORT)
		printf("-> algo_1 = K_SORT\n");
	if (config->algo_2 == GREEDY)
		printf("-> algo_2 = GREEDY\n");
	if (config->swap)
		printf("-> swap   = true\n");
	else
		printf("-> swap   = false\n");
	printf("-------------------- \n");
}
