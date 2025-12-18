#include "push_swap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void free_and_exit(t_stack *a, t_stack *b);
static void	_debug_print(t_stack *stack, char stack_name);

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
	debug_print_stack(&a, &b, BOTH);
	extract_from_a_to_b(&a, &b);
	// debug_print_stack(&a, &b, BOTH);
	rebuild_from_b_to_a(&a, &b);
	debug_print_stack(&a, &b, BOTH);
	stack_free(&a, &b);
	return (0);
}

static void free_and_exit(t_stack *a, t_stack *b)
{
	stack_free(a, b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

#include <stdio.h>	// TODO: tmp DEBUG
void debug_print_stack(t_stack *a, t_stack *b, t_stack_choice choice)
{
	fprintf(stderr, "\n--------------------------\n");
	if (choice == A)
		_debug_print(a, 'A');
	if (choice == B)
		_debug_print(b, 'B');
	else
	{
		_debug_print(a, 'A');
		fprintf(stderr, "--------------------------\n");
		_debug_print(b, 'B');
	}
	fprintf(stderr, "--------------------------\n\n");
}

static void	_debug_print(t_stack *stack, char stack_name)
{
	size_t	i;

	if (stack->count == 0)
	{
		fprintf(stderr, "[DEBUG] stack %c is EMPTY\n", stack_name);
		return ;
	}
	fprintf(stderr, "[DEBUG] stack %c\n", stack_name);
	i = 0;
	while (i < stack->count)
	{
		fprintf(stderr, "[DEBUG] [%zu] = %i\n", i, stack->values[i]);
		i++;
	}
	fprintf(stderr, "[DEBUG] count = %zu | cap = %zu\n", stack->count, stack->cap);
}
