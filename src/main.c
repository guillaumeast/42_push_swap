#include "args.h"
#include "state.h"
#include "moves.h"
#include "k_sort.h"
#include "sort_three.h"
#include "greedy.h"
#include "finish.h"
#include <stdlib.h>
#include <unistd.h>

# include "logs.h"

static bool	run_algos(t_state *state);
static int	free_and_print_error(t_state *state);

int	main(int argc, char **argv)
{
	t_args		args;
	t_state		state;

	// print_start(99, "main()");
	if (argc < 2)
		return (0);
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL));
	if (!state_init(&state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL));
	print_pass("state initialized\n");
	if (!run_algos(&state))
		return (free_and_print_error(&state));
	// TODO: check validity
	moves_print(&state.moves);
	state_free(&state);
	print_result("Done!");
	return (0);
}

static bool	run_algos(t_state *state)
{
	if (state->a.len < 150)
	{
		if (!pb(state, state->a.len - 3))
			return (false);
	}
	else if (!k_sort(state))
		return (false);
	print_pass("step 1 done\n");
	if (!sort_three(state))
		return (false);
	print_pass("sort_three done\n");
	if (!greedy(state))
		return (false);
	print_pass("greedy done\n");
	if (!finish(state))
		return (false);
	print_pass("finish done\n");
	optimize_moves(&state->moves);
	print_pass("moves optimized\n");
	return (true);
}

static int	free_and_print_error(t_state *state)
{
	if (state)
		state_free(state);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
