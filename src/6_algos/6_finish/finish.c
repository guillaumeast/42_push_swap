#include "libft.h"
#include "state.h"
#include "config.h"
#include "moves.h"

static bool	get_target_index(const t_stack *stack, size_t *ret);

bool finish(t_state *state, const t_config *config)
{
	size_t	target_index;

	(void)config;
	if (!get_target_index(&state->a, &target_index))
		return (false);
	if (target_index <= state->a.len / 2)
		return (ra(state, target_index));
	return (rra(state, state->a.len - target_index));
}

static bool	get_target_index(const t_stack *stack, size_t *ret)
{
	size_t	i;

	i = 0;
	while (i < stack->len)
	{
		if (stack->data[i] == 0)
		{
			*ret = modulo((long)i - (long)stack->offset, stack->len);
			return (true);
		}
		i++;
	}
	return (false);
}
