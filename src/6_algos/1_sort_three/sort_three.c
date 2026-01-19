#include "sort_three.h"
#include "moves.h"
#include "debug.h"	// TMP: remove before submit

bool	sort_three(t_state *state, t_config *config)
{
	uint	first_value;
	uint	second_value;

	if (stack_is_sorted(&state->a))
		return (true);
	fprintf(stderr, "\n[🔦 DEBUG] Executing sort_three...\n");
	if (!config->swap || state->b.len < 2)
		return (sa(&state->a, &state->moves));
	first_value = stack_get_value(&state->b, 0);
	second_value = stack_get_value(&state->b, 1);
	// NOTE: We don't check if B[0] > third_value because sb is "free" when combined with sa so it's ALWAYS better to have greater value higher in B, even if then B[1] < B[2] (because anyway B[0] is already < B[2])
	if (first_value > second_value)
		return (sa(&state->a, &state->moves));
	return (ss(&state->a, &state->b, &state->moves));	
}
