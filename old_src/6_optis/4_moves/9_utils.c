#include "opti_moves_priv.h"
// # include "debug.h"

void	pattern_init(t_pattern *dst, t_move a, t_move b, t_move cumul)
{
	dst->a_move = a;
	dst->b_move = b;
	dst->cumul_move = cumul;
	dst->a_count = 0;
	dst->b_count = 0;
	dst->cumul_count = 0;
	dst->cumulnew = 0;
	dst->no_op_count = 0;
}

void	set_move(t_move *dst, t_buff *moves, long index)
{
	if (index < 0 || index >= (long)moves->len)
	{
		// fprintf(stderr, "%s🎯 %s%3ld%s move = %sNO_OP%s\n", GREY, YELLOW, index, GREY, RED, NC);	// TODO: tmp debug
		*dst = NO_OP;
	}
	else
		*dst = (t_move)moves->data[index];
}
