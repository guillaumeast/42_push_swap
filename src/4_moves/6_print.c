#include "moves.h"
#include "moves_priv.h"
#include <unistd.h>
# include "print.h"
// TODO[2]: build the final buffer and print it at once to avoid several write() calls!

static void	print_move(t_move move);

void	moves_print(const t_buff *list)
{
	size_t	printed_bytes;
	t_move	move;

	print_title("print_moves()");
	printed_bytes = 0;
	while (printed_bytes < list->len)
	{
		move = (t_move)list->data[printed_bytes++];
		print_move(move);
	}
	print_result("moves printed            ⇢ %zu", list->len);
}

static void	print_move(t_move move)
{
	if (move == RR)
		write(1, "rr\n", 3);
	else if (move == RRR)
		write(1, "rrr\n", 4);
	else if (move == RA)
		write(1, "ra\n", 3);
	else if (move == RB)
		write(1, "rb\n", 3);
	else if (move == RRA)
		write(1, "rra\n", 4);
	else if (move == RRB)
		write(1, "rrb\n", 4);
	else if (move == SS)
		write(1, "ss\n", 3);
	else if (move == SA)
		write(1, "sa\n", 3);
	else if (move == SB)
		write(1, "sb\n", 3);
	else if (move == PA)
		write(1, "pa\n", 3);
	else if (move == PB)
		write(1, "pb\n", 3);
	else if (move == NO_OP)
		write(1, "NO_OP\n", 6);		// TMP: delete before submit
	else
		write(1, "UNKNOWN\n", 8);	// TMP: delete before submit
}
