#include "args.h"
#include "stack.h"
#include "moves.h"
#include "state.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>

static t_buff	*best_moves(t_state *in, t_state *out);
static int		free_and_print_error(t_state *state1, t_state *state2);

int	main(int argc, char **argv)
{
	t_args	args;
	t_state	initial_state;
	t_state	final_state;

	if (argc < 2)
		return (0);
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!state_init(&initial_state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	if (!state_init(&final_state, args.values, args.count))
		return (free_and_print_error(&initial_state, NULL));
	if (!best_moves(&initial_state, &final_state))
		return (free_and_print_error(&initial_state, &final_state));
	moves_print(&final_state.moves);
	// stack_print(&a, &b);
	state_free(&final_state);
	return (0);
}

/* TODO: refactor to handle state struct:
*		while cycle (i < CONFIG_COUNT)
*			state_dup(in)
*			state_init(tmp)
*			config_init(i)
*			config_run(config)
*			if (best_set == false) => best = tmp
*			else if (tmp.moves.len < best.moves.len) => {state_free(best), best = tmp}
*			else => state_free(tmp)
*		return (best)
*/
static bool best_moves(t_state *in, t_state *out)
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

static int	free_and_print_error(t_state *state1, t_state *state2)
{
	state_free(state1);
	state_free(state2);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
