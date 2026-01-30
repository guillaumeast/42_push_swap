#include "state.h"
#include <stdlib.h>
# include "logs.h"

// Caller must free dst (use state_free())
bool	state_init(t_state *dst, uint *values, size_t values_size)
{
	print_title("state_init()");
	if (!stack_init(&dst->a, &dst->b, values, values_size))
		return (print_error("state_init() ⇢ Unable to initialize stacks\n"), false);
	if (!buff_init(&dst->moves, values_size * 12))
		return (print_error("state_init() ⇢ Unable to initialize buffer\n"), false);
	print_result("State initialized");
	return (true);
}

// Caller must free dst (use state_free())
bool	state_dup(t_state *dst, const t_state *src)
{
	if (!stack_dup(&dst->a, &src->a))
		return (print_error("state_dup() ⇢ Unable to copy stack A\n"), false);
	if (!stack_dup(&dst->b, &src->b))
		return (print_error("state_dup() ⇢ Unable to copy stack B\n"), false);
	if (!buff_init(&dst->moves, src->moves.cap))
		return (print_error("state_dup() ⇢ Unable to init moves buffer\n"), false);
	if (!buff_append(&dst->moves, src->moves.data, (long)src->moves.len))
		return (print_error("state_dup() ⇢ Unable to copy moves\n"), false);
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
