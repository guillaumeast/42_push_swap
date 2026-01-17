#ifndef CONFIG_PRIV_H
# define CONFIG_PRIV_H

# include <sys/types.h>

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

uint	*generate_configs(size_t *count_ret);

#endif
