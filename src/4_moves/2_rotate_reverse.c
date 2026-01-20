#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	rrr(t_state *state, size_t count)
{
	stack_reverse_rotate(&state->a, count);
	stack_reverse_rotate(&state->b, count);
	return (move_add(RRR, count, &state->moves));
}

bool	rra(t_state *state, size_t count)
{
	stack_reverse_rotate(&state->a, count);
	return (move_add(RRA, count, &state->moves));
}

bool	rrb(t_state *state, size_t count)
{
	stack_reverse_rotate(&state->b, count);
	return (move_add(RRB, count, &state->moves));
}
