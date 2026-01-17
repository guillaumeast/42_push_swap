#include "state.h"

bool	state_init(t_state *dst, uint *values, size_t values_size)
{
	if (!stack_init(&dst->a, &dst->b, values, values_size))
		return (false);
	if (!buff_init(&dst->moves, values_size * 12))
		return (false);
	return (true);
}

bool	state_dup(t_state *dst, t_state *src)
{
	if (!stack_dup(&dst->a, &src->a))
		return (false);
	if (!stack_dup(&dst->b, &src->b))
		return (false);
	if (!buff_init(&dst->moves, src->moves.cap))
		return (false);
	if (!buff_append(&dst->moves, src->moves.data, (long)src->moves.len))
		return (false);
	return (true);
}

void	state_free(t_state *state)
{
	stack_free(&state->a);
	stack_free(&state->b);
	buff_free(&state->moves);
}
