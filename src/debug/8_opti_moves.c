#include "opti_moves.h"
#include "moves_priv.h"
# include "debug.h"

static void	print_move(t_move move);

bool	test_opti_moves(void)
{
	t_buff			moves;
	const t_move	pattern[] = {RR, RB, RR, RA, RR, PB, PA, PB, SA, SA, SA, SA};

	if (!buff_init(&moves, 64))
		return (false);
	for (size_t i = 0; i < sizeof(pattern) / sizeof(pattern[0]); i++)
		move_add((char)pattern[i], 1, &moves);
	fprintf(stderr, "\n%s⍟ moves  %4zu => ", BOLD_BLUE, moves.len);
	print_opti_moves(&moves, 0, 0, BOLD_BLUE, BOLD_BLUE, true);
	optimize_moves(&moves);
	fprintf(stderr, "%s⍟ moves  %4zu => ", BOLD_BLUE, moves.len);
	print_opti_moves(&moves, 0, 0, BOLD_BLUE, BOLD_BLUE, true);
	buff_free(&moves);
	return (true);
}

void	print_opti_moves(t_buff *moves, size_t start, size_t end, const char *color, const char *highlight, bool nl)
{
	size_t	i;
	t_move	move;

	if (moves->len > 15)
	{
		fprintf(stderr, "%s[...]%s\n", color, NC);
		return ;
	}
	fprintf(stderr, "%s[ ", color);
	i = 0;
	while (i < moves->len)
	{
		move = (t_move)moves->data[i];
		if (i >= start && i <= end)
			fprintf(stderr, "%s", highlight);
		print_move(move);
		if (i < moves->len - 1)
			fprintf(stderr, "%s - ", color);
		i++;
	}
	fprintf(stderr, "%s ]%s", color, NC);
	if (nl)
		fprintf(stderr, "\n");
}

static void	print_move(t_move move)
{
	if (move == RR)
		fprintf(stderr, "%5s", "RR");
	else if (move == RRR)
		fprintf(stderr, "%5s", "RRR");
	else if (move == RA)
		fprintf(stderr, "%5s", "RA");
	else if (move == RB)
		fprintf(stderr, "%5s", "RB");
	else if (move == RRA)
		fprintf(stderr, "%5s", "RRA");
	else if (move == RRB)
		fprintf(stderr, "%5s", "RRB");
	else if (move == SS)
		fprintf(stderr, "%5s", "SS");
	else if (move == SA)
		fprintf(stderr, "%5s", "SA");
	else if (move == SB)
		fprintf(stderr, "%5s", "SB");
	else if (move == PA)
		fprintf(stderr, "%5s", "PA");
	else if (move == PB)
		fprintf(stderr, "%5s", "PB");
	else if (move == NO_OP)
		fprintf(stderr, "%5s", "NO_OP");	// TMP: delete before submit
	else
		fprintf(stderr, "%5s", "UNKNOWN");	// TMP: delete before submit
}
