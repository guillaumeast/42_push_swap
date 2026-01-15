#ifndef MOVES_PRIV_H
# define MOVES_PRIV_H

# include "libft.h"

typedef enum e_move
{
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SA,
	SB,
	SS,
	PA,
	PB,
	NO_OP
}	t_move;

bool	move_add(char move, size_t count, t_buff *list);

#endif
