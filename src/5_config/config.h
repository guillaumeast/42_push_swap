#ifndef CONFIG_H
# define CONFIG_H

# include "state.h"
# include <stdbool.h>
# include <sys/types.h>

typedef struct s_chunk
{
	uint	size;
	uint	min;
	uint	max;
	uint	median;
	size_t	treated;
}	t_chunk;

typedef struct s_config
{
	const char	*algo_1_name;
	bool 		(*algo_1)(t_state *state, struct s_config *config);
	const char	*algo_2_name;
	bool 		(*algo_2)(t_state *state, struct s_config *config);
	const char	*opti_names;
	bool		swap;
	bool		median;
	bool		lis;
	t_chunk		chunk;
}	t_config;

typedef struct s_config_list
{
	t_config	*data;
	size_t		count;
}	t_config_list;

bool	config_init_list(t_config_list *config_list, size_t values_count);

// TODO: tmp debug
void	config_print_all(t_config **configs);
void	config_print(t_config *config, size_t index, bool print_index);

#endif
