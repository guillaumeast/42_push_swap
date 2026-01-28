#include "run.h"
#include "finish.h"
#include "opti_moves.h"

# include "debug.h"
# include "print.h"

void	run_init(t_run *dst, t_state *state, t_config *config)
{
	dst->state = *state;
	dst->config = *config;
}

bool	run_dup(t_run *dst, const t_run *src)
{
	if (!state_dup(&dst->state, &src->state))
		return (false);
	if (!config_dup(&dst->config, &src->config, src->state.a.len + src->state.b.len))
		return (state_free(&dst->state), false);
	return (true);
}

bool	run_run(t_run *run)
{
	print_title_top(true);
	print_title_mid(false, "run_config() ⇢ ");
	if (should_print(TITLE))
		config_print(&run->config, 0, false);
	if (!run->config.algo_1(&run->state, &run->config))
		return (print_error("algo_1 failed"), false);
	if (!stack_is_sorted(&run->state.a))
		return (print_error("A is not sorted after algo_1"), false);

	if (!run->config.algo_2(&run->state, &run->config))
		return (print_error("algo_2 failed"), false);
	if (!stack_is_sorted(&run->state.a))
		return (print_error("A is not sorted after algo_2"), false);
	if (run->state.b.len > 0)
		return (print_error("B is not empty after algo_2"), false);

	if (!finish(&run->state, &run->config))
		return (print_error("Finish algo failed"), false);
	if (stack_get_value(&run->state.a, 0) != 0)
		return (print_error("A[0] != 0 after finish()"), false);

	optimize_moves(&run->state.moves);

	print_result_mid(false, "");
	if (should_print(RESULT))
	{
		fprintf(stderr, "%-5zu ⇢ ", run->state.moves.len);
		config_print(&run->config, 0, false);
	}
	print_result_bot(true);
	return (true);
}

void	run_free(t_run *run)
{
	state_free(&run->state);
	config_free(&run->config);
}
