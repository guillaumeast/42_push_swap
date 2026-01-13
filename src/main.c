#include "args.h"
#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

// TODO: tmp DEBUG
#include <stdio.h>
static void	test(t_stack *a, t_stack *b);

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
	/*--- TEST ---*/
	test(&a, &b);
	/*--- TEST ---*/
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

static void	test(t_stack *a, t_stack *b)
{
	stack_print(a, b);

	// A moves
	printf("swap A\n");
	stack_swap(a, b, A);
	stack_print(a, b);

	printf("rotate A\n");
	stack_rotate(a, b, A, false);
	stack_print(a, b);

	printf("reverse rotate A\n");
	stack_rotate(a, b, A, true);
	stack_print(a, b);

	// Push from A to B
	printf("push from A to B\n");
	stack_push(a, b, B);
	stack_print(a, b);

	printf("push from A to B\n");
	stack_push(a, b, B);
	stack_print(a, b);

	printf("push from A to B\n");
	stack_push(a, b, B);
	stack_print(a, b);

	printf("push from A to B\n");
	stack_push(a, b, B);
	stack_print(a, b);

	// B moves
	printf("swap B\n");
	stack_swap(a, b, B);
	stack_print(a, b);

	printf("rotate B\n");
	stack_rotate(a, b, B, false);
	stack_print(a, b);

	printf("reverse rotate B\n");
	stack_rotate(a, b, B, true);
	stack_print(a, b);

	// Both moves
	printf("swap BOTH\n");
	stack_swap(a, b, BOTH);
	stack_print(a, b);

	printf("rotate BOTH\n");
	stack_rotate(a, b, BOTH, false);
	stack_print(a, b);

	printf("reverse rotate BOTH\n");
	stack_rotate(a, b, BOTH, true);
	stack_print(a, b);

	// Push from B to A
	printf("push from B to A\n");
	stack_push(b, a, A);
	stack_print(a, b);

	printf("push from B to A\n");
	stack_push(b, a, A);
	stack_print(a, b);

	printf("push from B to A\n");
	stack_push(b, a, A);
	stack_print(a, b);

	printf("push from B to A\n");
	stack_push(b, a, A);
	stack_print(a, b);
}
