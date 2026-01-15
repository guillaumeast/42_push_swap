#include "libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

static bool	check_arg(char *arg, int *ret, int *args_array, size_t size);
static bool	is_int(char *arg);
static bool	is_unique(int nb, int *array, size_t size);

bool	check_and_add_arg(char *arg, int *args, size_t *args_count)
{
	char	**splitted;
	size_t	i;

	if (!arg || !*arg)
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
	long	tmp;

	if (!is_int(arg))
		return (false);
	tmp = ft_atol(arg);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (false);
	if (!is_unique((int)tmp, args_array, size))
		return (false);
	*ret = (int)tmp;
	return (true);
}

static bool	is_int(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '\0')
		return (false);
	else if (arg[0] == '-' || arg[0] == '+')
	{
		if (arg[1] == '\0')
			return (false);
		else
			i = 1;
	}
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (i <= 11);
}

static bool	is_unique(int nb, int *array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (array[i] == nb)
			return (false);
		i++;
	}
	return (true);
}
