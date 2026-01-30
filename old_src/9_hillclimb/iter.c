#include "run.h"
#include "iter.h"

# include "logs.h"

#define DEFAULT_TARGET(input_count)	input_count / 4

static void	iter_update(t_iter *iter);

bool	iter_init(t_iter *iter, const t_run *src, long target, long gap)
{
	if (target < 0 || gap < 0 || target - gap < 0)
		return (false);
	iter->run_src = src;
	iter->target = target;
	iter->gap = gap;
	iter->run1.config.chunk_size = (size_t)target - (size_t)gap;
	iter->run2.config.chunk_size = (size_t)target;
	iter->run3.config.chunk_size = (size_t)target + (size_t)gap;
	print_info("target = %3ld | gap = %3ld ⇢ size1 = %3zu | size2 = %3zu | size3 = %3zu\n", target, gap, iter->run1.config.chunk_size, iter->run2.config.chunk_size, iter->run3.config.chunk_size);
	iter->best = -1;
	iter->end_reach = false;
	return (true);
}

bool	iter_exec(t_iter *iter)
{
	print_title("iter_exec()");
	if (!run_run(&iter->run1, &iter->run_src->state, &iter->run_src->config))
		return (false);
	if (!run_run(&iter->run2, &iter->run_src->state, &iter->run_src->config))
		return (run_free(&iter->run1), false);
	if (!run_run(&iter->run3, &iter->run_src->state, &iter->run_src->config))
		return (run_free(&iter->run2), run_free(&iter->run1), false);
	if (iter->run1.state.moves.len <= iter->run2.state.moves.len)
	{
		if (iter->run3.state.moves.len < iter->run1.state.moves.len)
			iter->best = 3;
		else
			iter->best = 1;
	}
	else if (iter->run2.state.moves.len < iter->run3.state.moves.len)
		iter->best = 2;
	else
		iter->best = 3;
	iter_update(iter);
	print_result("1 = %3zu | 2 = %3zu | 3 = %3zu => best = %i", iter->run1.state.moves.len, iter->run2.state.moves.len, iter->run3.state.moves.len, iter->best);
	return (true);
}

static void	iter_update(t_iter *iter)
{
	long	new_target;
	long	new_gap;

	new_target = iter->target;
	new_gap = iter->gap;
	if (iter->best == 1)
		new_target = iter->target - (iter->gap * 2);
	else if (iter->best == 3)
		new_target = iter->target + (iter->gap * 2);
	else if (iter->best == 2)
		new_gap = iter->gap / 2;
	if (new_target < 0)
		new_target = 0;
	if (new_gap > 0 && new_target - new_gap < 0)
		new_gap = new_target;
	if (new_gap <= 0)
		iter->end_reach = true;
	iter->target = new_target;
	iter->gap = new_gap;
	print_result("target = %3ld | gap = %3ld | end_reach = %s", iter->target, iter->gap, iter->end_reach ? "true" : "false");
}

void	iter_free(t_iter *iter)
{
	run_free(&iter->run1);
	run_free(&iter->run2);
	run_free(&iter->run3);
}
