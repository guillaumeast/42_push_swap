#include "sort_three.h"
#include "moves.h"

bool	sort_three(t_state *state)
{
	uint	first_value;
	uint	second_value;

	if (stack_is_sorted(&state->a))
		return (true);
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	if (first_value > second_value)
		return (sa(state));
	return (ss(state));
}
