#ifndef ARGS_H
# define ARGS_H

#include <stddef.h>

typedef struct s_args
{
	int		*values;
	size_t	count;
}	t_args;

t_args	*parse_args(int argc, char **argv);

#endif
