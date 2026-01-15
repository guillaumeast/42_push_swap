#include "args.h"
#include "stack.h"
#include "k_sort.h"
#include "greedy.h"
#include <stdlib.h>
#include <unistd.h>

// TODO: tmp DEBUG
#include <stdio.h>
// static void	test(t_stack *a, t_stack *b);

static bool	try_k_sort_and_greedy(t_stack *a, t_stack *b, t_buff *move_list);
static bool finish(t_stack *a, t_move move, size_t count, t_buff *move_list);
static int	free_and_print_error(t_stack *a, t_stack *b);

// void	test(t_stack *a, t_stack *b, t_buff *move_list)
// {
// 	char	move;
// 	int		value;

// 	printf("===> [INITIAL STATE]\n");
// 	stack_print(a, b);
// 	for (size_t i = 0; i < a->len / 2; i++)
// 	{
// 		move = (char)PB;
// 		buff_append(move_list, &move, 1);
// 		stack_push(a, b, B);
// 	}
// 	for (size_t i = 0; i < a->len / 2; i++)
// 	{
// 		move = (char)RA;
// 		buff_append(move_list, &move, 1);
// 		stack_rotate(a, b, A, false);
// 	}
// 	printf("===> [AFTER PUSHES AND ROTATES]\n");
// 	moves_print(move_list);
// 	stack_print(a, b);

// 	for (size_t i = 0; i < a->len; i++)
// 	{
// 		value = stack_get_value(a, i);
// 		printf("===> A->values[%zu] = %i\n", i, value);
// 	}
// 	for (int i = 0; i < (int)a->len * 2; i++)
// 	{
// 		value = stack_get_target_index(a, i - 1);
// 		printf("===> Target index for %i = %i\n", i, value);
// 	}
// }

int	main(int argc, char **argv)
{
	t_args	args;
	t_stack	a;
	t_stack	b;
	t_buff	move_list;

	if (argc < 2)
		return (0);
	// printf("\033[32m✔\033[0m argc > 1\n");
	if (!parse_args(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	// printf("\033[32m✔\033[0m args parsed\n");
	stack_init(&a, args.values, args.count);
	// printf("\033[32m✔\033[0m stack A initialized\n");
	if (!buff_init(&move_list, args.count * args.count))
		return (free_and_print_error(&a, &b));
	// printf("\033[32m✔\033[0m move_list initialized\n");
	if (!stack_init(&b, NULL, 0))
		return (free_and_print_error(&a, &b));
	// printf("\033[32m✔\033[0m stack B initialized\n");
	if (!try_k_sort_and_greedy(&a, &b, &move_list))
		return (buff_free(&move_list), free_and_print_error(&a, &b));
	// printf("\033[32m✔\033[0m algo finished\n");
	moves_print(&move_list);
	// printf("done\n");
	free(a.data);
	free(b.data);
	return (0);
}

static bool	try_k_sort_and_greedy(t_stack *a, t_stack *b, t_buff *move_list)
{
	size_t	target_index;
	t_move	move;
	size_t	count;

	// stack_print(a, b);
	// printf("[BEFORE K_SORT] => moves = %zu\n", move_list->len);
	if (!k_sort(a, b, move_list))
		return (false);
	// moves_print(move_list);
	// stack_print(a, b);
	// printf("[BEFORE GREEDY] => moves = %zu\n", move_list->len);
	if (!greedy(a, b, move_list))
		return (false);
	// moves_print(move_list);
	// stack_print(a, b);
	// printf("[AFTER GREEDY] => moves = %zu\n", move_list->len);
	target_index = (size_t)stack_get_target_index(a, -1);
	if (target_index <= a->size / 2)
	{
		move = RA;
		count = target_index;
	}
	else
	{
		move = RRA;
		count = a->size - target_index;
	}
	if (!finish(a, move, count, move_list))
		return (false);
	// stack_print(a, b);
	// printf("[AFTER FINISH] => moves = %zu\n", move_list->len);
	return (true);
}

static bool finish(t_stack *a, t_move move, size_t count, t_buff *move_list)
{
	bool	reverse;
	char	move_as_char;

	move_as_char = (char)move;
	if (move == RA)
		reverse = false;
	else if (move == RRA)
		reverse = true;
	else
		return (false);
	while (count--)
	{
		stack_rotate(a, NULL, A, reverse);
		if (!buff_append(move_list, &move_as_char, 1))
			return (false);
	}
	return (true);
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

// static void	test(t_stack *a, t_stack *b)
// {
// 	stack_print(a, b);

// 	// A moves
// 	printf("swap A\n");
// 	stack_swap(a, b, A);
// 	stack_print(a, b);

// 	printf("rotate A\n");
// 	stack_rotate(a, b, A, false);
// 	stack_print(a, b);

// 	printf("reverse rotate A\n");
// 	stack_rotate(a, b, A, true);
// 	stack_print(a, b);

// 	// Push from A to B
// 	printf("push from A to B\n");
// 	stack_push(a, b, B);
// 	stack_print(a, b);

// 	printf("push from A to B\n");
// 	stack_push(a, b, B);
// 	stack_print(a, b);

// 	printf("push from A to B\n");
// 	stack_push(a, b, B);
// 	stack_print(a, b);

// 	printf("push from A to B\n");
// 	stack_push(a, b, B);
// 	stack_print(a, b);

// 	// B moves
// 	printf("swap B\n");
// 	stack_swap(a, b, B);
// 	stack_print(a, b);

// 	printf("rotate B\n");
// 	stack_rotate(a, b, B, false);
// 	stack_print(a, b);

// 	printf("reverse rotate B\n");
// 	stack_rotate(a, b, B, true);
// 	stack_print(a, b);

// 	// Both moves
// 	printf("swap BOTH\n");
// 	stack_swap(a, b, BOTH);
// 	stack_print(a, b);

// 	printf("rotate BOTH\n");
// 	stack_rotate(a, b, BOTH, false);
// 	stack_print(a, b);

// 	printf("reverse rotate BOTH\n");
// 	stack_rotate(a, b, BOTH, true);
// 	stack_print(a, b);

// 	// Push from B to A
// 	printf("push from B to A\n");
// 	stack_push(b, a, A);
// 	stack_print(a, b);

// 	printf("push from B to A\n");
// 	stack_push(b, a, A);
// 	stack_print(a, b);

// 	printf("push from B to A\n");
// 	stack_push(b, a, A);
// 	stack_print(a, b);

// 	printf("push from B to A\n");
// 	stack_push(b, a, A);
// 	stack_print(a, b);
// }
