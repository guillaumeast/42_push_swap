#include "libft.h"
#include "args.h"
#include "args_priv.h"
#include <stdlib.h>

bool	args_parse(int argc, char **argv, t_args *args)
{
	int		*raw_args;
	size_t	i;

	argc--;
	argv++;
	i = 0;
	args->count = 0;
	while (i < (size_t)argc)
		args->count += str_count_words(argv[i++], ' ');
	raw_args = malloc(args->count * sizeof * raw_args);
	if (!raw_args)
		return (false);
	i = 0;
	args->count = 0;
	while (i < (size_t)argc)
	{
		if (!convert_arg(argv[i], raw_args, &args->count))
			return (free(raw_args), false);
		i++;
	}
	args->values = normalize(raw_args, args->count);
	free(raw_args);
	if (!args->values)
		return (false);
	return (true);
}
