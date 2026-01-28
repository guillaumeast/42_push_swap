#include "libft.h"
#include "args.h"
#include "args_priv.h"
#include <stdlib.h>
# include "print.h"

static bool	convert_arg(char *arg, int *args, size_t *args_count);
static bool	check_arg(char *arg, int *ret, int *args_array, size_t size);

bool	args_parse(int argc, char **argv, t_args *args)
{
	int		*raw_args;
	size_t	i;

	// print_start(1, "args_parse()");
	print_title("args_parse()");
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
	print_pass("Parsed as integers       ⇢ %3zu\n", i);
	args->values = normalize(raw_args, args->count);
	free(raw_args);
	print_result("arguments parsed         ⇢ %3zu", args->count);
	if (!args->values)
		return (false);
	return (true);
}

static bool	convert_arg(char *arg, int *args, size_t *args_count)
{
	char	**splitted;
	size_t	i;

	if (!*arg)
		return (false);
	splitted = str_split(arg, ' ');
	if (!splitted)
		return (false);
	i = 0;
	while (splitted[i])
	{
		if (!check_arg(splitted[i], &args[*args_count], args, *args_count))
			return (str_array_free(&splitted), false);
		(*args_count)++;
		i++;
	}
	str_array_free(&splitted);
	return (true);
}

static bool	check_arg(char *arg, int *ret, int *args_array, size_t size)
{
	size_t	i;
	int		value;

	if (!parse_int(arg, &value))
		return (false);
	i = 0;
	while (i < size)
	{
		if (args_array[i] == value)
			return (false);
		i++;
	}
	*ret = value;
	return (true);
}
