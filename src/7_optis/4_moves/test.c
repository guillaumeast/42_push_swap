#include "moves.h"
#include "opti_moves.h"
#include "moves_priv.h"
# include "debug.h"

bool	test_opti_moves(void)
{
	t_buff			moves;
	const t_move	pattern[] = {RA, RR, RB, PA, PB, PA, RA, RB};

	if (!buff_init(&moves, 64))
		return (false);
	for (size_t i = 0; i < sizeof(pattern) / sizeof(pattern[0]); i++)
		move_add((char)pattern[i], 1, &moves);
	fprintf(stderr, "🧪%s moves initial   (%zu)%s\n", GREY, moves.len, NC);
	moves_print(&moves);
	if (!optimize_moves(&moves))
	{
		fprintf(stderr, "\n🧪%s optimize_moves() failed!%s\n", RED, NC);
		buff_free(&moves);
		return (false);
	}
	fprintf(stderr, "\n🧪%s moves optimized (%zu)%s\n", GREY, moves.len, NC);
	moves_print(&moves);
	buff_free(&moves);
	return (true);
}
