#ifndef ITER_H
# define ITER_H

#include "run.h"

typedef struct s_iter
{
	const t_run	*run_src;
	long		target;
	long		gap;
	t_run		run1;
	t_run		run2;
	t_run		run3;
	int			best;
	bool		end_reach;
}	t_iter;

bool	iter_init(t_iter *iter, const t_run *src, long target, long gap);
bool	iter_exec(t_iter *iter);
void	iter_free(t_iter *iter);

#endif
