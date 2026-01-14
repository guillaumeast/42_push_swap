#ifndef ARGS_H
# define ARGS_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_args
{
	int		*values;
	size_t	count;
}	t_args;

bool	parse_args(int argc, char **argv, t_args *args);

#endif
