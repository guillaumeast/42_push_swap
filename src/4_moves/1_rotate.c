#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	rr(t_state *state, size_t count)
{
	stack_rotate(&state->a, count);
	stack_rotate(&state->b, count);
	return (move_add(RR, count, &state->moves));
}

bool	ra(t_state *state, size_t count)
{
	stack_rotate(&state->a, count);
	return (move_add(RA, count, &state->moves));
}

bool	rb(t_state *state, size_t count)
{
	stack_rotate(&state->b, count);
	return (move_add(RB, count, &state->moves));
}
