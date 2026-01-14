#include "libft.h"
#include "args.h"
#include "check_priv.h"
#include "normalize_priv.h"
#include <stdbool.h>
#include <stdlib.h>

static size_t	get_args_count(int argc, char **argv);
static bool		check_and_add_arg(t_args *args, char *str);

# include <stdio.h>
bool	parse_args(int argc, char **argv, t_args *args)
{
	int		i;

	args->values = NULL;
	args->count = get_args_count(argc, argv);
	if (args->count == 0)
		return (false);
	args->values = malloc(args->count * sizeof *args->values);
	if (!args->values)
		return (false);
	args->count = 0;
	i = 1;
	while (i < argc)
	{
		if (!check_and_add_arg(args, argv[i]))
			return (free(args->values), false);
		i++;
	}
	if (!normalize(args->values, args->count))
		return (free(args->values), false);
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

static bool	check_and_add_arg(t_args *args, char *str)
{
	char	**splitted;
	size_t	i;

	if (!str || !*str)
		return (false);
	splitted = str_split(str, ' ');
	if (!splitted)
		return (false);
	i = 0;
	while (splitted[i])
	{
		if (!check_arg(
			splitted[i], 
			&args->values[args->count], 
			args->values, 
			args->count
		))
			return (str_array_free(&splitted), false);
		args->count++;
		i++;
	}
	str_array_free(&splitted);
	return (true);
}
