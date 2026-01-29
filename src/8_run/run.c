#include "run.h"
#include "finish.h"
#include "opti_moves.h"

# include "debug.h"
# include "print.h"

// bool	run_configs(t_state *state, t_configs *configs)
// {
// 	size_t	i;
// 	t_run	run;
// 	t_run	curr;

// 	print_start(1, "run_configs()");
// 	i = 0;
// 	while (i < configs->count && configs->data[i].algo_1 != k_sort)
// 		i++;
// 	if (i >= configs->count)
// 		return (false);
// 	run_init(&run, state, &configs->data[i]);
// 	i = 50;
// 	while (i < state->a.len && i < 150)
// 	{
// 		if (!run_dup(&curr, &run))
// 			return (false);
// 		curr.config.chunk_size = i;
// 		// print_info("Run inited with chunksize = %3zu | moves = %3zu\n", curr.config.chunk_size, curr.state.moves.len);
// 		if (!run_run(&curr))
// 			return (false);
// 		// print_info("Run done   with chunksize = %s%3zu%s | moves = %s%3zu%s\n", YELLOW, curr.config.chunk_size, GREY, GREEN, curr.state.moves.len, NC);
// 		i++;
// 		run_free(&curr);
// 	}
// 	hillclimb(&run);
// 	state_free(state);
// 	// config_free(&configs->data[i]);
// 	*state = run.state;
// 	// configs->data[i] = run.config;
// 	print_result("run_configs() done");
// 	return (true);
// }

static bool	algo_1_check(const t_run *run);
static bool	algo_2_check(const t_run *run);
static bool	finish_check(const t_run *run);
static void	print_run_result(const t_run *run, long best_so_far);

bool	run_all(t_run *dst, const t_state *state, const t_configs *configs)
{
	size_t	i;
	t_run	curr;

	print_title("run_all()");

	if (!run_run(dst, state, &configs->data[0]))
		return (false);
	i = 0;
	while (i < configs->count)
	{
		print_title(false, "Comparing 2 runs...");
		if (!run_run(&curr, state, &configs->data[i]))
			return (run_free(dst), false);
		print_run_result(&curr, (long)dst->state.moves.len);
		if (curr.state.moves.len < dst->state.moves.len)
		{
			run_free(dst);
			*dst = curr;
		}
		else
			run_free(&curr);
		i++;
	}

	print_result_mid(false, "best moves               ⇢ %3zu ⇢ ", state->moves.len);
	fprintf(stderr, "%s", YELLOW);
	if (should_print(RESULT))
		config_print(&dst->config, 0, false);
	fprintf(stderr, "%s", NC);
	print_result_bot(true);
	return (true);
}

bool	run_run(t_run *dst, const t_state *state, const t_config *config)
{
	print_title(false, "run_run()");
	if (should_print(TITLE))
	{
		fprintf(stderr, "%s", GREY);
		config_print(config, 0, false);
		fprintf(stderr, "%s", NC);
	}
	if (!run_init(dst, state, config))
		return (false);
	if (!dst->config.algo_1(&dst->state, &dst->config))
		return (print_error("algo_1 failed"), run_free(dst), false);
	if (!algo_1_check(dst))	// TMP: remove before submit
		return (run_free(dst), false);
	if (!dst->config.algo_2(&dst->state, &dst->config))
		return (print_error("algo_2 failed"), run_free(dst), false);
	if (!algo_2_check(dst))	// TMP: remove before submit
		return (run_free(dst), false);
	if (!finish(&dst->state, &dst->config))
		return (print_error("Finish algo failed"), false);
	if (!finish_check(dst))	// TMP: remove before submit
		return (run_free(dst), false);
	optimize_moves(&dst->state.moves);
	print_run_result(dst, -1);
	return (true);
}

bool	run_init(t_run *dst, const t_state *state, const t_config *config)
{
	if (!state_dup(&dst->state, state))
		return (false);
	if (!config_dup(&dst->config, config, state->a.len + state->b.len))
		return (state_free(&dst->state), false);
	print_pass("run initialized\n");
	return (true);
}

bool	run_dup(t_run *dst, const t_run *src)
{
	if (!state_dup(&dst->state, &src->state))
		return (false);
	if (!config_dup(&dst->config, &src->config, src->state.a.len + src->state.b.len))
		return (state_free(&dst->state), false);
	return (true);
}

void	run_free(t_run *run)
{
	state_free(&run->state);
	config_free(&run->config);
}

/* -------------------- TMP: remove before submit -------------------- */

static bool	algo_1_check(const t_run *run)
{
	if (!stack_is_sorted(&run->state.a))
		return (print_error("A is not sorted after algo_1"), false);
	return (true);
}

static bool	algo_2_check(const t_run *run)
{
	if (!stack_is_sorted(&run->state.a))
		return (print_error("A is not sorted after algo_2"), false);
	if (run->state.b.len > 0)
		return (print_error("B is not empty after algo_2"), false);
	return (true);
}

static bool	finish_check(const t_run *run)
{
	if (!stack_is_sorted(&run->state.a))
		return (print_error("A is not sorted after finish()"), false);
	if (stack_get_value(&run->state.a, 0) != 0)
		return (print_error("A[0] != 0 after finish()"), false);
	return (true);
}

static void	print_run_result(const t_run *run, long best_so_far)
{
	long		delta;

	print_result_mid(false, "%s%-8zu %s", YELLOW, run->state.moves.len, GREY);
	if (should_print(RESULT))
	{
		if (best_so_far < 0)
			fprintf(stderr, "                ⇢ ");
		else
		{
			delta = (long)run->state.moves.len - best_so_far;
			if (delta > 0)
				fprintf(stderr, "%s %+8ld%s       ⇢ ", RED, delta, GREY);
			else if (delta == 0)
				fprintf(stderr, "        %s0%s       ⇢ ", YELLOW, GREY);
			else
				fprintf(stderr, "%s %+8ld%s       ⇢ ", GREEN, delta, GREY);
		}
		config_print(&run->config, 0, false);
		fprintf(stderr, "%s", NC);
	}
	print_result_bot(true);
}
