#include "args.h"
#include "moves.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>
#include "run.h"
# include "logs.h"

static int	free_and_print_error(t_state *state, t_configs *configs);

int	main(int argc, char **argv)
{
	t_args		args;
	t_state		state;
	t_configs	configs;
	t_run		best;

	if (argc < 2)
		return (0);
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!state_init(&state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	if (!config_init_list(&configs, &state))
		return (free_and_print_error(&state, NULL));
	if (!run_all(&best, &state, &configs))
		return (free_and_print_error(&state, &configs));
	moves_print(&best.state.moves);	// TMP: comment it to make outputs readable
	state_free(&state);
	run_free(&best);
	free(configs.data);
	return (0);
}

static int	free_and_print_error(t_state *state, t_configs *configs)
{
	if (state)
		state_free(state);
	if (configs && configs->lis_set)
	{
		lis_free(&configs->lis);
		lis_free(&configs->lis_swap);
	}
	if (configs && configs->data)
		free(configs->data);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
