#include "libft.h"
#include "args.h"
#include "moves.h"
#include "state.h"
#include "naive.h"
#include "greedy.h"
#include "finish.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>	// TODO: tmp debug

static bool	run_configs(t_state *inital_state, t_config **configs, t_buff *best_moves);
static bool	abort_config(t_state *state, t_buff *moves, const char *error);
static int	free_and_print_error(t_state *state, t_config **configs);

int	main(int argc, char **argv)
{
	t_args		args;
	t_state		initial_state;
	t_config	**configs;
	t_buff		best_moves;

	if (argc < 2)
		return (0);
	printf("\n");
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!state_init(&initial_state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	configs = config_get_list();
	if (!configs)
		return (free_and_print_error(&initial_state, NULL));
	buff_init(&best_moves, 0);
	if (!run_configs(&initial_state, configs, &best_moves))
		return (free_and_print_error(&initial_state, configs));
	// moves_print(&best_moves);
	// stack_print(&a, &b);
	state_free(&initial_state);
	config_list_free(&configs);
	buff_free(&best_moves);
	return (0);
}

static bool	run_configs(t_state *inital_state, t_config **configs, t_buff *best_moves)
{
	size_t		i;
	t_config	*config;
	t_config	*best_config;
	t_state		state;

	// TODO: add (bool (*algo)(t_state *state, t_config *config) ptr to config struct)
	i = 0;
	config = configs[0];
	while (config)
	{
		// TODO: free state when failed
		fprintf(stderr, "ℹ️  ===> Running config %zu\n", i);
		if (!state_dup(&state, inital_state))
			return (abort_config(&state, best_moves, "Unable to duplicate state"));
		if (!config->algo_1(&state, config))
			return (abort_config(&state, best_moves, "algo_1 failed"));
		if (!config->algo_2(&state, config))
			return (abort_config(&state, best_moves, "algo_2 failed"));
		if (!stack_is_sorted(&state.a) || state.b.len > 0)
			return (abort_config(&state, best_moves, "A is not sorted and/or B is not empty"));
		if (!finish(&state, config))
			return (abort_config(&state, best_moves, "Finish algo failed"));
		fprintf(stderr, "ℹ️  ===> Moves = %zu\n\n", state.moves.len);
		if (best_moves->cap == 0 || state.moves.len < best_moves->len)
		{
			buff_free(best_moves);
			*best_moves = state.moves;
			best_config = config;
			stack_free(&state.a);
			stack_free(&state.b);
		}
		else
			state_free(&state);
		config = configs[++i];
	}
	fprintf(stderr, "✅ ========> Best config = ");
	config_print(best_config, 0, false);
	fprintf(stderr, "✅ ========> Best moves  = %zu\n\n", best_moves->len);
	return (true);
}

static bool	abort_config(t_state *state, t_buff *moves, const char *error)
{
	state_free(state);
	buff_free(moves);
	ft_dprintf(STDERR_FILENO, "‼️ %s, stopping\n", error);
	return (false);
}

static int	free_and_print_error(t_state *state, t_config **configs)
{
	state_free(state);
	config_list_free(&configs);
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
