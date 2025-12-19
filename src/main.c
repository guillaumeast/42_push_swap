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
	if (!parse_args(argc, argv, &a, &b))
		free_and_exit(&a, &b);
	if (!stack_convert_to_sorted_indexes(&a))
		free_and_exit(&a, &b);

	/*---------- TODO: tmp DEBUG + versionning ----------*/
	fprintf(stderr, "===> START\n");
	debug_print(&a, &b);
	fprintf(stderr, "\n===> STEP 1\n");
	step_1(&a, &b);
	if (b.count > 0 || !is_sorted(&a))
	{
		fprintf(stderr, "\n===> STEP 2\n");
		step_2(&a, &b);
		debug_print(&a, &b);
		debug_print_move_count();
	}
	fprintf(stderr, "\n===> FINISH\n");
	finish(&a, &b);
	debug_print(&a, &b);
	debug_print_move_count();
	/*---------------------------------------------------*/

	stack_free(&a, &b);
	return (0);
}

static void free_and_exit(t_stack *a, t_stack *b)
{
	stack_free(a, b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
