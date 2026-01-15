#include "libft.h"
#include "args.h"
#include "check_priv.h"
#include "normalize_priv.h"
#include <stdbool.h>
#include <stdlib.h>

static size_t	get_args_count(int argc, char **argv);

bool	parse_args(int argc, char **argv, t_args *args)
{
	int	i;
	int	*raw_array;

	args->values = NULL;
	args->count = get_args_count(argc, argv);
	if (args->count == 0)
		return (false);
	raw_array = malloc(args->count * sizeof *raw_array);
	if (!raw_array)
		return (false);
	args->count = 0;
	i = 1;
	while (i < argc)
	{
		if (!check_and_add_arg(argv[i], raw_array, &args->count))
			return (free(raw_array), false);
		i++;
	}
	args->values = normalize(raw_array, args->count);
	free(raw_array);
	if (!args->values)
		return (false);
	return (args);
}

static size_t	get_args_count(int argc, char **argv)
{
	int		i;
	size_t	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		count += str_count_words(argv[i], ' ');
		i++;
	}
	return (count);
}
