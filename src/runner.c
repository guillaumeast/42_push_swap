#include "config.h"
#include "finish.h"
#include "opti_moves.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit
# include "print.h"	// TMP: remove before submit

typedef struct s_run
{
	t_state		state;
	t_config	config;
}	t_run;

static bool	run_config(t_state *state, t_config *config, long best_count);

bool	run_configs(t_state *state, t_configs *configs)
{
	size_t	i;
	t_run	best;
	t_run	curr;
	long	best_score;

	print_title("run_configs()");
	if (!state_dup(&best.state, state))
		return (false);
	best_score = -1;
	i = 0;
	while (i < configs->count)
	{
		curr.config = configs->data[i];
		if (!state_dup(&curr.state, state))
			return (false);
		if (!run_config(&curr.state, &curr.config, best_score))
			return (false);
		if (best_score == -1 || curr.state.moves.len < best.state.moves.len)
		{
			best_score = (long)curr.state.moves.len;
			state_free(&best.state);
			best = curr;
		}
		else
			state_free(&curr.state);
		i++;
	}
	state_free(state);
	*state = best.state;
	print_result_mid(false, "best moves               ⇢ %3zu ⇢ ", state->moves.len);
	fprintf(stderr, "%s", YELLOW);
	if (should_print(RESULT))
		config_print(&best.config, 0, false);
	fprintf(stderr, "%s", NC);
	print_result_bot(true);
	return (true);
}

static bool	run_config(t_state *state, t_config *config, long best_count)
{
	print_title_top(true);
	print_title_mid(false, "run_config() ⇢ ");
	if (should_print(TITLE))
		config_print(config, 0, false);
	if (!config->algo_1(state, config))
		return (print_error("algo_1 failed"), false);
	if (!stack_is_sorted(&state->a))
		return (print_error("A is not sorted after algo_1"), false);

	if (!config->algo_2(state, config))
		return (print_error("algo_2 failed"), false);
	if (!stack_is_sorted(&state->a))
		return (print_error("A is not sorted after algo_2"), false);
	if (state->b.len > 0)
		return (print_error("B is not empty after algo_2"), false);

	if (!finish(state, config))
		return (print_error("Finish algo failed"), false);
	if (stack_get_value(&state->a, 0) != 0)
		return (print_error("A[0] != 0 after finish()"), false);

	optimize_moves(&state->moves);

	print_result_mid(false, "");
	if (should_print(RESULT))
	{
		if (best_count < 0)
			fprintf(stderr, "%s%-5zu%s        ", YELLOW, state->moves.len, GREY);
		else
			fprintf(stderr, "%s%-5zu ⇢ %+5ld%s", state->moves.len < (size_t)best_count ? GREEN : RED, state->moves.len, (long)state->moves.len - best_count, GREY);
		fprintf(stderr, " ⇢ ");
		config_print(config, 0, false);
	}
	print_result_bot(true);
	return (true);
}
