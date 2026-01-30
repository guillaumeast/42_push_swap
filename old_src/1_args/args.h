#ifndef ARGS_H
# define ARGS_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_args
{
	uint	*values;
	size_t	count;
}	t_args;

bool	args_parse(int argc, char **argv, t_args *args);

#endif
