#include "push_swap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void free_and_exit(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	if (!stack_init(&a, &b, (size_t)argc - 1))
		free_and_exit(&a, &b);
	if (!parse_args(argv, &a))
		free_and_exit(&a, &b);
	if (!stack_convert_to_sorted_indexes(&a))
		free_and_exit(&a, &b);
	extract_from_a_to_b(&a, &b);
	// TODO: rebuild
	stack_free(&a, &b);
	return (0);
}

static void free_and_exit(t_stack *a, t_stack *b)
{
	stack_free(a, b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
