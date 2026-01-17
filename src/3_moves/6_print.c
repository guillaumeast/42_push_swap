#include "libft.h"
#include "moves.h"

static void	print_move(t_move move);

void	moves_print(t_buff *list)
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
		ft_printf("RR\n");
	else if (move == RRR)
		ft_printf("RRR\n");
	else if (move == RA)
		ft_printf("RA\n");
	else if (move == RB)
		ft_printf("RB\n");
	else if (move == RRA)
		ft_printf("RRA\n");
	else if (move == RRB)
		ft_printf("RRB\n");
	else if (move == SS)
		ft_printf("SS\n");
	else if (move == SA)
		ft_printf("SA\n");
	else if (move == SB)
		ft_printf("SB\n");
	else if (move == PA)
		ft_printf("PA\n");
	else if (move == PB)
		ft_printf("PB\n");
	else if (move == NO_OP)
		ft_printf("NO_OP\n");			// TODO: delete before submit
	else
		ft_printf("????????????\n");	// TODO: delete before submit
}
