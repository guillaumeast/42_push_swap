#include "libft.h"
#include "push_swap.h"
#include <limits.h>

static bool	is_numeric(char *arg);
static bool is_duplicate(int nb, t_stack *stack);

bool	parse_args(char **argv, t_stack *a)
{
	size_t	i;
	char	*arg;
	long	tmp;

	i = 0;
	while (i < a->cap)
	{
		arg = argv[i + 1];
		if (!is_numeric(arg))
			return (false);
		if (ft_strlen(arg) > 11)
			return (false);
		tmp = ft_atol(argv[i + 1]);
		if (tmp < INT_MIN || tmp > INT_MAX)
			return (false);
		if (is_duplicate((int)tmp, a))
			return (false);
		a->values[i] = (int)tmp;
		i++;
	}
	return (true);
}

static bool	is_numeric(char *arg)
{
	size_t	i;

	if (arg[0] != '-' && arg[0] != '+' && (arg[0] < '0' || arg[0] > '9'))
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool is_duplicate(int nb, t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->count)
	{
		if (stack->values[i] == nb)
			return (true);
		i++;
	}
	return (false);
}
