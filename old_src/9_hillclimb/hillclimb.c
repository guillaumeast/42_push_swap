#include "run.h"
#include "iter.h"

# include "logs.h"

#define DEF_TARGET_DIV	4
#define DEF_GAP_DIV		8

static void	keep_best_and_free(t_run *dst, t_iter *src);

bool	hillclimb(t_run *run)
{
	t_iter	iter;

	print_start(2, "hillclimb()");
	if (!iter_init(&iter, run, run->state.a.len / DEF_TARGET_DIV, run->state.a.len / DEF_GAP_DIV))
		return (false);
	while (true)
	{
		if (!iter_exec(&iter))
			return (iter_free(&iter), false);
		print_info("end_reach = %s\n", iter.end_reach ? "true" : "false");
		if (iter.end_reach)
			break ;
		iter_free(&iter);
		if (!iter_init(&iter, run, iter.target, iter.gap))
			return (false);
	}
	run_free(run);
	keep_best_and_free(run, &iter);
	print_result("Best moves with chunk_size ⇢ %3zu ⇢ %5zu", run->config.chunk_size, run->state.moves.len);
	return (false);
	// return (true);
}

static void	keep_best_and_free(t_run *dst, t_iter *src)
{
	if (src->best == 1)
	{
		*dst = src->run1;
		run_free(&src->run2);
		run_free(&src->run3);
	}
	else if (src->best == 2)
	{
		*dst = src->run2;
		run_free(&src->run1);
		run_free(&src->run3);
	}
	else if (src->best == 3)
	{
		*dst = src->run3;
		run_free(&src->run1);
		run_free(&src->run2);
	}
	else
		iter_free(src);
}
