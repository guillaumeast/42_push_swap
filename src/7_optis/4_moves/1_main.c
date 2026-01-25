#include "libft.h"
#include "opti_moves_priv.h"

bool	optimize_moves(t_buff *moves)
{
	t_buff	final_moves;
	size_t	i;

	if (!buff_init(&final_moves, moves->len))
		return (false);
	while (true)
	{
		if (!merge_all(&final_moves, moves, &i))
			return (buff_free(&final_moves), false);
		// TODO: other optimizations
		if (final_moves.len >= moves->len)
		{
			buff_free(&final_moves);
			return (true);
		}
		buff_free(moves);
		*moves = final_moves;
	}
	return (false);
}

