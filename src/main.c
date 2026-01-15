#include "args.h"
#include "stack.h"
#include "moves.h"
#include "config.h"
#include "push.h"
#include "k_sort.h"
#include "greedy.h"
#include "finish.h"
#include <stdlib.h>
#include <unistd.h>

static t_buff	*best_moves(t_stack *a, t_stack *b);
static t_buff	*try(t_stack *a, t_stack *b, t_config *config);
static int		free_and_print_error(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_args	args;
	t_stack	a;
	t_stack	b;
	t_buff	*move_list;

	if (argc < 2)
		return (0);
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!stack_init(&a, &b, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	move_list = best_moves(&a, &b);
	if (!move_list)
		return (free_and_print_error(&a, &b));
	moves_print(move_list);
	// stack_print(&a, &b);
	buff_free(move_list);
	free(move_list);
	free(a.data);
	free(b.data);
	return (0);
}

static t_buff	*best_moves(t_stack *a, t_stack *b)
{
	t_buff		*best_moves;
	t_buff		*current_moves;
	t_config	config;

	config.step_1 = NAIVE;
	config.step_2 = GREEDY;
	config.swap = false;
	best_moves = try(a, b, &config);
	if (!best_moves)
		return (NULL);
	config.swap = true;
	current_moves = try(a, b, &config);
	if (!current_moves)
		return (buff_free(best_moves), free(best_moves), NULL);
	if (current_moves->len < best_moves->len)
	{
		buff_free(best_moves);
		free(best_moves);
		best_moves = current_moves;
	}
	else
	{
		buff_free(current_moves);
		free(current_moves);
	}
	return (best_moves);
}

static t_buff	*try(t_stack *a, t_stack *b, t_config *config)
{
	t_buff	*moves;
	t_stack	a_dup;
	t_stack	b_dup;

	if (!stack_dup(&a_dup, a))
		return (NULL);
	if (!stack_dup(&b_dup, b))
		return (free(a_dup.data), NULL);
	moves = malloc(sizeof * moves);
	if (!moves)
		return (free(a_dup.data), free(b_dup.data), NULL);
	if (!buff_init(moves, a->len * 12))
		return (free(a_dup.data), free(b_dup.data), free(moves), NULL);
	if (config->step_1 == NAIVE)
		if (!push_to_b(&a_dup, &b_dup, config, moves))
			return (free(a_dup.data), free(b_dup.data), buff_free(moves), free(moves), NULL);
	if (config->step_2 == GREEDY)
		if (!greedy(&a_dup, &b_dup, moves))
			return (free(a_dup.data), free(b_dup.data), buff_free(moves), free(moves), NULL);
	if (!finish(&a_dup, moves))
		return (free(a_dup.data), free(b_dup.data), buff_free(moves), free(moves), NULL);
	free(a_dup.data);
	free(b_dup.data);
	return (moves);
}
// TODO: add config_init and config_free functions
// TODO: add stacks and t_buff directly inside config struct

static int	free_and_print_error(t_stack *a, t_stack *b)
{
	if (a && a->data)
		free(a->data);
	if (b && b->data)
		free(b->data);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
