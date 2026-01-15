#ifndef CONFIG_H
# define CONFIG_H

# include "libft.h"
# include "stack.h"

typedef enum e_algo
{
	NAIVE,
	LIS,
	CHUNK,
	KSORT,
	GREEDY,
	NONE
}	t_algo;

typedef struct s_config
{
	t_stack	a;
	t_stack	b;
	t_buff	moves;
	t_algo	step_1;
	t_algo	step_2;
	bool	swap;
	bool	error;
}	t_config;

bool	config_init(t_stack *a, t_stack *b, t_config *ret);
bool	config_run(t_config *config);
void	config_free(t_config *config);

#endif
