#include "state.h"
#include "window.h"
#include "moves.h"
#include <stdlib.h>

typedef struct s_target
{
	size_t	index;
	uint	value;
}	t_target;

static void	find(t_state *state, t_window *window, t_target *ret_target);
static bool	rotate(t_state *state, size_t index);
static bool	exec(t_state *state, t_window *window, uint value);

bool	k_sort(t_state *state)
{
	t_window	window;
	t_target	target;

	window_init(&window, state->a.len, state->a.len / 6);
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		find(state, &window, &target);
		if (!rotate(state, target.index))
			return (false);
		if (!exec(state, &window, target.value))
			return (false);
		window_update(&window, target.value, state->a.len);
	}
	free(window.treated);
	return (true);
}

static void	find(t_state *state, t_window *window, t_target *ret_target)
{
	size_t	index;
	uint	value;

	index = 0;
	value = stack_get_value(&state->a, 0);
	while (value < window->min || value >= window->max)
		value = stack_get_value(&state->a, (long)++index);
	ret_target->index = index;
	ret_target->value = value;
}

static bool	rotate(t_state *state, size_t index)
{
	if (index <= state->a.len / 2)
		return (ra(state, index));
	return (rra(state, state->a.len - index));
}

static bool	exec(t_state *state, t_window *window, uint value)
{
	if (!pb(state, 1))
		return (false);
	if (value <= window->med)
		return (rb(state, 1));
	return (true);
}

