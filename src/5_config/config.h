#ifndef CONFIG_H
# define CONFIG_H

# include "state.h"
# include "lis.h"
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
	bool		opti_swap_b;
	bool		opti_median;
	bool		opti_lis;
	bool		opti_lis_swap;
	t_chunk		chunk;
	t_lis		lis;
}	t_config;

typedef struct s_config_list
{
	t_config	*data;
	size_t		count;
	bool		lis_set;
	t_lis		lis;
	t_lis		lis_swap;
}	t_config_list;

bool	config_init_list(t_config_list *configs, t_state *state);

#endif
