#include "push_swap.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	parse_stdin(t_stack *a, t_stack *b);
static void free_and_exit(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &a, &b))
		free_and_exit(&a, &b);
	if (!stack_convert_to_sorted_indexes(&a))
		free_and_exit(&a, &b);
	debug_print(&a, &b);	// TODO: tmp DEBUG
	if (!parse_stdin(&a, &b))
		free_and_exit(&a, &b);
	if (b.count == 0 && is_sorted(&a))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	stack_free(&a, &b);
	return (0);
}

static bool	parse_stdin(t_stack *a, t_stack *b)
{
	// TODO: add gnl (optimized with t_buff ?) to libft
	// while gnl() != NULL
	// check validity
	// execute
}

bool	is_sorted(t_stack *stack)
{
	size_t	i;
	int		breaks;

	breaks = 0;
	i = 0;
	while (i < stack->count)
	{
		if (stack->values[i] > stack->values[(i + 1) % stack->count])
			breaks++;
		i++;
	}
	return (breaks <= 1);
}

static void free_and_exit(t_stack *a, t_stack *b)
{
	stack_free(a, b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
