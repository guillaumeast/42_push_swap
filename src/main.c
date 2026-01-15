#include "args.h"
#include "stack.h"
#include "moves.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>

static t_buff	*best_moves(t_stack *a, t_stack *b);
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
	t_config	config_1;
	t_config	config_2;
	t_buff		*res;

	if (!config_init(a, b, &config_1))
		return (NULL);
	config_1.step_1 = NAIVE;
	config_1.step_2 = GREEDY;
	if (!config_run(&config_1) || config_1.error)
		return (config_free(&config_1), NULL);
	if (!config_init(a, b, &config_2))
		return (config_free(&config_1), NULL);
	config_2.step_1 = NAIVE;
	config_2.step_2 = GREEDY;
	config_2.swap = true;
	if (!config_run(&config_2) || config_2.error)
		return (config_free(&config_1), config_free(&config_2), NULL);
	res = malloc(sizeof *res);
	if (!res)
		return (config_free(&config_1), config_free(&config_2), NULL);
	if (config_1.moves.len < config_2.moves.len)
	{
		config_free(&config_2), stack_free(&config_1.a), stack_free(&config_1.b);
		res->data = config_1.moves.data;
		res->cap = config_1.moves.cap;
		res->len = config_1.moves.len;
		return (res);
	}
	else
	{
		config_free(&config_1), stack_free(&config_2.a), stack_free(&config_2.b);
		res->data = config_2.moves.data;
		res->cap = config_2.moves.cap;
		res->len = config_2.moves.len;
		return (res);
	}
}
// TODO: don't put t_buff inside config struct (it will be easier to free)
// TODO: algos interface should be (t_stack *a, t_stack *b, t_opti *opti, t_buff *moves)

static int	free_and_print_error(t_stack *a, t_stack *b)
{
	if (a && a->data)
		free(a->data);
	if (b && b->data)
		free(b->data);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
