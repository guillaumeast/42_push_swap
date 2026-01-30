#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	ss(t_state *state)
{
	stack_swap(&state->a);
	stack_swap(&state->b);
	return (move_add(SS, 1, &state->moves));
}

bool	sa(t_state *state)
{
	if (state->a.len < 2)
		return (true);
	stack_swap(&state->a);
	return (move_add(SA, 1, &state->moves));
}

bool	sb(t_state *state)
{
	if (state->b.len < 2)
		return (true);
	stack_swap(&state->b);
	return (move_add(SB, 1, &state->moves));
}
