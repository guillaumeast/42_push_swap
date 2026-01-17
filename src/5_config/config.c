#include "libft.h"
#include "config.h"
#include <stdlib.h>

/* ----- from generator.c ----- */
uint		*generate_configs(size_t *count_ret);

static t_config	*generate_new_config(t_config *last_config);
static	t_config **normalize_config(t_config **raw_list);

t_config	**config_get_list(void)
{
	size_t		i;
	t_config	*last_config;
	t_config	**raw_list;

	raw_list = malloc(CONFIG_COUNT * sizeof * raw_list);
	if (!raw_list)
		return (NULL);
	raw_list[0] = malloc(sizeof ** raw_list);
	if (!raw_list[0])
		return (free(raw_list), NULL);
	raw_list[0]->algo_1 = 1;
	raw_list[0]->algo_2 = 1;
	raw_list[0]->optis = 0;
	i = 1;
	while (i < CONFIG_COUNT)
	{
		last_config = raw_list[i - 1];
		raw_list[i] = generate_new_config(last_config);
		if (!raw_list[i])
			return (config_list_free(&raw_list), NULL);
		i++;
	}
	return (normalize_config(raw_list));
}

static t_config	*generate_new_config(t_config *last_config)
{
	t_config	*new_config;

	new_config = malloc(sizeof * new_config);
	if (!new_config)
		return (NULL);
	if (last_config->algo_1 != ALGO_1_COUNT - 1)
		new_config->algo_1 = last_config->algo_1 * 2;
	else
		new_config->algo_1 = last_config->algo_1;
	if (last_config->algo_2 != ALGO_2_COUNT - 1)
		new_config->algo_2 = last_config->algo_2 * 2;
	else
		new_config->algo_2 = last_config->algo_2;
	new_config->optis = last_config->optis + 1;	// Cycle it for each algo !!
	return (new_config);
}

static	t_config **normalize_config(t_config **raw_list)
{

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

// TODO
bool	config_run(t_config *config)
{
	if (config->step_1 == NAIVE)
		if (!push_to_b(config))
			return (false);
	if (config->step_2 == GREEDY)
		if (!greedy(config))
			return (false);
	if (!stack_is_sorted(&config->a))
	{
		config->error = true;
		return (true);
	}
	return (finish(config));
}
