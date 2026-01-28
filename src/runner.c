#include "config.h"
#include "finish.h"
#include "opti_moves.h"
#include "k_sort.h"
#include "run.h"
#include "hillclimb.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit
# include "print.h"	// TMP: remove before submit

bool	run_configs(t_state *state, t_configs *configs)
{
	size_t	i;
	t_run	run;

	print_title("run_configs()");
	i = 0;
	while (i < configs->count && configs->data[i].algo_1 != k_sort)
		i++;
	if (i >= configs->count)
		return (false);
	run_init(&run, state, &configs->data[i]);
	hillclimb(&run);
	state_free(state);
	// config_free(&configs->data[i]);
	*state = run.state;
	// configs->data[i] = run.config;
	print_result("run_configs() done");
	return (true);
}

// bool	run_configs(t_state *state, t_configs *configs)
// {
// 	size_t	i;
// 	t_run	best;
// 	t_run	curr;
// 	long	best_score;

// 	print_title("run_configs()");
// 	if (!state_dup(&best.state, state))
// 		return (false);
// 	best_score = -1;
// 	i = 0;
// 	while (i < configs->count)
// 	{
// 		curr.config = configs->data[i];
// 		if (!state_dup(&curr.state, state))
// 			return (false);
// 		if (!run_config(&curr.state, &curr.config, best_score))
// 			return (false);
// 		if (best_score == -1 || curr.state.moves.len < best.state.moves.len)
// 		{
// 			best_score = (long)curr.state.moves.len;
// 			state_free(&best.state);
// 			best = curr;
// 		}
// 		else
// 			state_free(&curr.state);
// 		i++;
// 	}
// 	state_free(state);
// 	*state = best.state;
// 	print_result_mid(false, "best moves               ⇢ %3zu ⇢ ", state->moves.len);
// 	fprintf(stderr, "%s", YELLOW);
// 	if (should_print(RESULT))
// 		config_print(&best.config, 0, false);
// 	fprintf(stderr, "%s", NC);
// 	print_result_bot(true);
// 	return (true);
// }


