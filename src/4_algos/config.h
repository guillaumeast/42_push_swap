#ifndef CONFIG_H
# define CONFIG_H

# include <stdbool.h>

typedef enum e_step_1
{
	NAIVE,
	LIS,
	CHUNK,
	KSORT
}	t_step_1;

typedef enum e_step_2
{
	GREEDY
}	t_step_2;

typedef struct s_config
{
	t_step_1	step_1;
	t_step_2	step_2;
	bool		swap;
}	t_config;

#endif
