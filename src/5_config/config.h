#ifndef CONFIG_H
# define CONFIG_H

# include <stdbool.h>
# include <sys/types.h>

/*
* Note: to add a new algo:
* 1. Add the corresponding binary value in config_priv.h
* 2. Add the corresponding macro to the input_init() array (algos_1 or algos_2)
* Note: to add a new opti:
* 1. Add the corresponding bool to this struct
* 2. Add the corresponding binary values to config_priv.h (OPTI + OPTI_COMPAT)
* 3. Add the corresponding macros to the input_init() arrays (optis and optis_compat)
*/
typedef struct s_config
{
	uint	algo_1;
	uint	algo_2;
	bool	swap;
}	t_config;

// Returns a NULL terminated list of t_config (owned by the caller, use config_list_free() to free it)
t_config	**config_get_list(void);
// Frees each t_config and the array (array pointer is set to NULL)
void		config_list_free(t_config ***config_list);

// TODO: tmp debug
void	config_print(t_config *config);

#endif
