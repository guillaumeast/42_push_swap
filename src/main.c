#include "libft.h"
#include "args.h"
#include "moves.h"
#include "state.h"
#include "finish.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>
# include "debug.h"	// TMP: remove before submit

static bool	run_configs(t_state *inital_state, t_config_list *configs, t_buff *best_moves);
static bool	abort_config(t_state *state, t_buff *moves, const char *error);
static int	free_and_print_error(t_state *state, t_config_list *configs);

int	main(int argc, char **argv)
{
	t_args			args;
	t_state			initial_state;
	t_config_list	configs;
	t_buff			best_moves;

	if (argc < 2)
		return (0);
	fprintf(stderr, "\n");
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL, NULL));
	if (!state_init(&initial_state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL, NULL));
	if (!config_init_list(&configs, &initial_state))
		return (free_and_print_error(&initial_state, NULL));
	buff_init(&best_moves, 0);
	if (!run_configs(&initial_state, &configs, &best_moves))
		return (free_and_print_error(&initial_state, &configs));
	// moves_print(&best_moves);	// TMP: uncomment before submit (It's commented to make debug outputs readable)
	fprintf(stdout, " ");			// TMP: remove before submit (It's here for parsing tester)
	state_free(&initial_state);
	free(configs.data);
	buff_free(&best_moves);
	return (0);
}

static bool	run_configs(t_state *inital_state, t_config_list *configs, t_buff *best_moves)
{
	size_t		i;
	t_config	config;
	t_config	best_config;
	t_state		state;

	i = 0;
	while (i < configs->count)
	{
		config = configs->data[i];
		fprintf(stderr, "ℹ️  Config = \033[34m");
		config_print(&config, i, false);
		fprintf(stderr, "\033[0m");
		if (!state_dup(&state, inital_state))
			return (abort_config(&state, best_moves, "Unable to duplicate state"));
		if (!config.algo_1(&state, &config))
			return (abort_config(&state, best_moves, "algo_1 failed"));
		if (!config.algo_2(&state, &config))
			return (abort_config(&state, best_moves, "algo_2 failed"));
		// TMP: remove before submit (4 lines)
		if (!stack_is_sorted(&state.a))
			return (abort_config(&state, best_moves, "A is not sorted"));
		if (state.b.len > 0)
			return (abort_config(&state, best_moves, "B is not empty"));
		if (!finish(&state, &config))
			return (abort_config(&state, best_moves, "Finish algo failed"));
		if (stack_get_value(&state.a, 0) != 0)
			return (abort_config(&state, best_moves, "A[0] != 0"));
		if (best_moves->cap == 0 || state.moves.len < best_moves->len)
		{
			// TMP: remove before submit (4 lines)
			if (best_moves->cap == 0)
				fprintf(stderr, "ℹ️  Moves  = \033[33m%zu\033[0m\n\n", state.moves.len);
			else
				fprintf(stderr, "ℹ️  Moves  = \033[32m%zu (%+ld)\033[0m\n\n", state.moves.len, (long)state.moves.len - (long)best_moves->len);
			buff_free(best_moves);
			*best_moves = state.moves;
			best_config = config;
			free(state.a.data);
			free(state.b.data);
		}
		else
		{
			// TMP: remove before submit (1 line + curvy brackets)
			fprintf(stderr, "ℹ️  Moves  = \033[31m%zu (%+ld)\033[0m\n\n", state.moves.len, (long)state.moves.len - (long)best_moves->len);
			state_free(&state);
		}
		i++;
	}
	// TMP: remove before submit (3 lines)
	fprintf(stderr, "✅ ===> Best config => \033[34m");
	config_print(&best_config, 0, false);
	fprintf(stderr, "\033[0m✅ ===> Best moves  => \033[32m%zu\033[0m\n\n", best_moves->len);
	return (true);
}

static bool	abort_config(t_state *state, t_buff *moves, const char *error)
{
	stack_print(&state->a, &state->b);
	state_free(state);
	buff_free(moves);
	fprintf(stderr, "‼️ %s, stopping\n", error);	// TMP: remove before submit
	return (false);
}

static int	free_and_print_error(t_state *state, t_config_list *configs)
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
