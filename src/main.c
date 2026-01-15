#include "args.h"
#include "stack.h"
#include "moves.h"
#include "k_sort.h"
#include "greedy.h"
#include "finish.h"
#include <stdlib.h>
#include <unistd.h>

static bool	try_k_sort_and_greedy(t_stack *a, t_stack *b, t_buff *move_list);
static int	free_and_print_error(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_args	args;
	t_stack	a;
	t_stack	b;
	t_buff	move_list;

	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!stack_init(&a, &b, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	if (!buff_init(&move_list, args.count * 20))
		return (free_and_print_error(&a, &b));
	if (!try_k_sort_and_greedy(&a, &b, &move_list))
		return (buff_free(&move_list), free_and_print_error(&a, &b));
	moves_print(&move_list);
	free(a.data);
	free(b.data);
	return (0);
}

static bool	try_k_sort_and_greedy(t_stack *a, t_stack *b, t_buff *move_list)
{
	if (!k_sort(a, b, move_list))
		return (false);
	if (!greedy(a, b, move_list))
		return (false);
	return (finish(a, move_list));
}

static int	free_and_print_error(t_stack *a, t_stack *b)
{
	if (a && a->data)
		free(a->data);
	if (b && b->data)
		free(b->data);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
