#include "libft.h"
#include "args.h"
#include "check_priv.h"
#include "replace_priv.h"
#include <stdbool.h>
#include <stdlib.h>

static size_t	get_args_count(int argc, char **argv);
static size_t	count_words(char *str);
static bool		check_and_add_arg(t_args *args, char *str);
static void		free_str_array(char **str_array);

t_args	*parse_args(int argc, char **argv)
{
	t_args	*res;
	int		i;

	res = malloc(sizeof * res);
	if (!res)
		return (NULL);
	res->values = NULL;
	res->count = get_args_count(argc, argv);
	if (res->count == 0)
		return (res);
	res->values = malloc(res->count * sizeof *res->values);
	if (!res->values)
		return (free(res), NULL);
	res->count = 0;
	i = 1;
	while (i < argc)
	{
		if (!check_and_add_arg(res, argv[i]))
			return (free(res->values), free(res), NULL);
		i++;
	}
	if (!replace_by_sorted_indexes(res->values, res->count))
		return (free(res->values), free(res), NULL);
	return (res);
}

static size_t	get_args_count(int argc, char **argv)
{
	int		i;
	size_t	count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		count += count_words(argv[i]);
		i++;
	}
	return (count);
}

static size_t	count_words(char *str)
{
	bool	in_word;
	size_t	count;

	in_word = false;
	count = 0;
	while (*str)
	{
		if (!in_word && *str != ' ')
		{
			in_word = true;
			count++;
		}
		else if (in_word && *str == ' ')
			in_word = false;
		str++;
	}
	return (count);
}

static bool	check_and_add_arg(t_args *args, char *str)
{
	char	**splitted;
	size_t	i;

	splitted = ft_split(str, ' ');
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
			return (free_str_array(splitted), false);
		args->count++;
		i++;
	}
	free_str_array(splitted);
	return (true);
}

static void	free_str_array(char **str_array)
{
	size_t	i;

	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}
