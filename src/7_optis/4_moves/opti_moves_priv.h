#ifndef OPTI_MOVES_PRIV_H
# define OPTI_MOVES_PRIV_H

#include "moves_priv.h"

typedef struct s_pattern
{
	t_move	a_move;
	size_t	a_count;
	t_move	b_move;
	size_t	b_count;
	t_move	cumul_move;
	size_t	cumul_count;
	size_t	cumul_new;
}	t_pattern;

/* ---------- merge.c ---------- */

bool	merge_all(t_buff *dst, t_buff *src, size_t *index);

/* ---------- utils.c ---------- */

void	pattern_init(t_pattern *dst, t_move a, t_move b, t_move cumul);
void	set_move(t_move *dst, t_buff *moves, long index);

#endif
