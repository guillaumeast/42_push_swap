#include "args.h"
#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

// TODO: tmp DEBUG
#include <stdio.h>

static void	free_and_exit(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_args	*args;
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	args = parse_args(argc, argv);
	if (!args)
		free_and_exit(NULL, NULL);
	stack_init(&a, args->values, args->count);
	free(args);
	if (!stack_init(&b, NULL, a.cap))
		free_and_exit(&a, &b);
	stack_print(&a, &b);
	free(a.values);
	free(b.values);
	return (0);
}

static void	free_and_exit(t_stack *a, t_stack *b)
{
	if (a && a->values)
		free(a->values);
	if (b && b->values)
		free(b->values);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
