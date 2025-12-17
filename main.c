#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

static void	parse_args(int argc, char **argv, t_stack *a);

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	a = malloc(((unsigned long)argc - 1) * sizeof *a);
	if (!a)
		return (1);
	b = malloc(((unsigned long)argc - 1) * sizeof *b);
	if (!b)
	{
		free(a);
		return (1);
	}
	parse_args(argc, argv, &a);
	// TODO: exec
	free(a);
	free(b);
	return (0);
}

static void	parse_args(int argc, char **argv, t_stack *a)
{
	size_t	i;
	size_t	count;
	long	tmp;

	i = 0;
	count = (size_t)argc - 2;
	while (i < count)
	{
		// TODO: check only numbers
		tmp = ft_atol(argv[i + 1]);
		// TODO: check no dupliacted
		// TODO: check int limits
		(*a)[i] = (int)tmp;
	}
}
