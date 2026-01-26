#include "config_priv.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_input
{
	const uint	*algos_1;
	const uint	*algos_2;
	const uint	*optis;
	const uint	*optis_compat;
	size_t		algos_1_count;
	size_t		algos_2_count;
	size_t		optis_count;
	size_t		couples_count;
	size_t		optis_max_combo_count;
	size_t		configs_count;
}	t_input;

static void		input_init(t_input *input);
static size_t	add_couples(t_input *input, uint *configs);
static size_t	add_optis(t_input *input, uint *configs);
static bool		opti_is_valid(uint opti_compatibilities, uint config);

bool	generate_raw_configs(uint **ret_list, size_t *ret_count)
{
	t_input	input;

	input_init(&input);
	*ret_list = malloc(input.configs_count * sizeof ** ret_list);
	if (!*ret_list)
		return (false);
	*ret_count = add_couples(&input, *ret_list);
	*ret_count += add_optis(&input, *ret_list);
	return (true);
}

static void	input_init(t_input *input)
{
	// static const uint	algos_1[] = {NAIVE, CHUNK, K_SORT};
	// static const uint	algos_2[] = {GREEDY};
	static const uint	algos_1[] = {K_SORT};
	static const uint	algos_2[] = {GREEDY};
	static const uint	optis[] = {};
	static const uint	optis_compat[] = {};
	// static const uint	optis[] = {MEDIAN, LIS, LIS_SWAP, SWAP};
	// static const uint	optis_compat[] = {MEDIAN_COMPAT, LIS_COMPAT, LIS_SWAP_COMPAT, SWAP_COMPAT};

	input->algos_1 = algos_1;
	input->algos_1_count = sizeof(algos_1) / sizeof(algos_1[0]);
	input->algos_2 = algos_2;
	input->algos_2_count = sizeof(algos_2) / sizeof(algos_2[0]);
	input->optis = optis;
	input->optis_compat = optis_compat;
	input->optis_count = sizeof(optis) / sizeof(optis[0]);
	input->couples_count = input->algos_1_count * input->algos_2_count;
	input->optis_max_combo_count = 1U << input->optis_count;
	input->configs_count = input->couples_count * input->optis_max_combo_count;
}

static size_t	add_couples(t_input *input, uint *configs)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (i < input->algos_1_count)
	{
		j = 0;
		while (j < input->algos_2_count)
		{
			configs[k] = input->algos_1[i] | input->algos_2[j];
			k++;
			j++;
		}
		i++;
	}
	return (k);
}

/*
* combined_optis						=> the combined optis (00000001, then 00000010, then 00000011, ..., 11111111)
* couples_index							=> the index of the base config from which optis will be added
* target_index							=> the index in which the new config will be inserted
* combined_optis & (1 << opti_index)	=> checks if the current opti is enabled in the combined opti set
* config |= input->optis[opti_index]	=> add the compatible opti to base config
* if (opti_index == input->optis_count)	=> checks if all optis have been validated (if yes, insert the new config into configs array)
*/
static size_t	add_optis(t_input *input, uint *configs)
{
	uint	combined_optis;
	size_t	couples_index;
	size_t	opti_index;
	uint	config;
	size_t	target_index;

	couples_index = 0;
	target_index = input->couples_count;
	while (couples_index < input->couples_count)
	{
		combined_optis = (1U << OPTI_OFFSET);
		while (combined_optis < (input->optis_max_combo_count << OPTI_OFFSET))
		{
			config = configs[couples_index];
			opti_index = 0;
			while (opti_index < input->optis_count)
			{
				if ((combined_optis & input->optis[opti_index]) != 0)
				{
					if (!opti_is_valid(input->optis_compat[opti_index], config))
						break ;
					config |= input->optis[opti_index];
				}
				opti_index++;
			}
			if (opti_index == input->optis_count)
				configs[target_index++] = config;
			combined_optis += (1U << OPTI_OFFSET);
		}
		couples_index++;
	}
	return (target_index - input->couples_count);
}

/*
* at least one algo must be compatible with this opti
* all optis already enabled must be compatible with this opti
*/
static bool	opti_is_valid(uint opti_compatibilities, uint config)
{
	uint	algos_mask;
	uint	algos;
	uint	opti_list;
	uint	compatibilities;

	algos_mask = (ALGO_1_MASK | ALGO_2_MASK);
	algos = (config & algos_mask);
	compatibilities = (opti_compatibilities & algos_mask);
	if ((algos & compatibilities) == 0)
		return (false);
	opti_list = (config & OPTI_MASK);
	compatibilities = (opti_compatibilities & OPTI_MASK);
	return ((opti_list & compatibilities) == opti_list);
}
