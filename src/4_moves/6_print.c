#include "moves.h"
#include "moves_priv.h"
#include <unistd.h>

// TODO[1]: add moves_normalize() to delete useless moves (NO_OP, PB+PA, RA+RRA, RB+RRB, RR+RRR, SA+SA, SB+SB, SS+SS...)
// TODO[2]: build the final buffer and print it at once to avoid several write() calls!

static void	print_move(t_move move);

void	moves_print(const t_buff *list)
{
	size_t	printed_bytes;
	t_move	move;

	printed_bytes = 0;
	while (printed_bytes < list->len)
	{
		move = (t_move)list->data[printed_bytes++];
		print_move(move);
	}
}

static void	print_move(t_move move)
{
	if (move == RR)
		write(1, "RR\n", 3);
	else if (move == RRR)
		write(1, "RRR\n", 4);
	else if (move == RA)
		write(1, "RA\n", 3);
	else if (move == RB)
		write(1, "RB\n", 3);
	else if (move == RRA)
		write(1, "RRA\n", 4);
	else if (move == RRB)
		write(1, "RRB\n", 4);
	else if (move == SS)
		write(1, "SS\n", 3);
	else if (move == SA)
		write(1, "SA\n", 3);
	else if (move == SB)
		write(1, "SB\n", 3);
	else if (move == PA)
		write(1, "PA\n", 3);
	else if (move == PB)
		write(1, "PB\n", 3);
	else if (move == NO_OP)
		write(1, "NO_OP\n", 6);		// TMP: delete before submit
	else
		write(1, "UNKNOWN\n", 8);	// TMP: delete before submit
}
