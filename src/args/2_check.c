#include "libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

static bool	is_numeric(char *arg);
static bool	is_unique(int nb, int *array, size_t size);

bool	check_arg(char *arg, int *ret, int *args_array, size_t size)
{
	long	tmp;

	if (!is_numeric(arg) || ft_strlen(arg) > 11)
		return (false);
	tmp = ft_atol(arg);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (false);
	if (!is_unique((int)tmp, args_array, size))
		return (false);
	*ret = (int)tmp;
	return (true);
}

static bool	is_numeric(char *arg)
{
	size_t	i;

	if (arg[0] == '\0')
		return (false);
	if (arg[0] != '-' && arg[0] != '+' && (arg[0] < '0' || arg[0] > '9'))
		return (false);
	if ((arg[0] == '-' || arg[0] == '+') && (arg[1] < '0' || arg[1] > '9'))
		return (false);
	i = 1;
	while (arg[i] != '\0' && arg[i] != ' ')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
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
