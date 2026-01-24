#include "state.h"
#include <stdlib.h>

// Caller must free dst (use state_free())
bool	state_init(t_state *dst, uint *values, size_t values_size)
{
	if (!stack_init(&dst->a, &dst->b, values, values_size))
		return (false);
	if (!buff_init(&dst->moves, values_size * 12))
		return (false);
	return (true);
}

// Caller must free dst (use state_free())
bool	state_dup(t_state *dst, const t_state *src)
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
	if (state->a.data)
		free(state->a.data);
	if (state->b.data)
		free(state->b.data);
	buff_free(&state->moves);
}
