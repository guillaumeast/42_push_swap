#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	pa(t_state *state, size_t count)
{
	if (state->b.len == 0)
		return (true);
	stack_push(&state->b, &state->a, count);
	return (move_add(PA, count, &state->moves));
}

bool	pb(t_state *state, size_t count)
{
	if (state->a.len == 0)
		return (true);
	stack_push(&state->a, &state->b, count);
	return (move_add(PB, count, &state->moves));
}
