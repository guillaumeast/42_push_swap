#ifndef CONFIG_H
# define CONFIG_H

# include <stdbool.h>

typedef struct s_config
{
	int		algo_1;
	int		algo_2;
	bool	swap;
	bool	opti_2;
	bool	opti_3;
}	t_config;

t_config	**config_get_list(void);
void		config_list_free(t_config ***config_list);

#endif
