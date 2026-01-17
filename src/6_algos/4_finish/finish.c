#include "libft.h"
#include "state.h"
#include "config.h"
#include "moves.h"

static bool	get_target_index(t_stack *stack, size_t *ret);

bool finish(t_state *state, t_config *config)
{
	size_t	target_index;

	if (!get_target_index(&config->a, &target_index))
		return (false);
	if (target_index <= config->a.len / 2)
	{
		// TODO: switch commented parts for submit / debug
		// if (!ra(&config->a, target_index, &config->moves))
		// 	return (false);
		if (!move_add(RA, target_index, &config->moves))
			return (false);
	}
	else
	{
		// TODO: switch commented parts for submit / debug
		// if (!rra(&config->a, config->a.len - target_index, &config->moves))
		// 	return (false);
		if (!move_add(RRA, config->a.len - target_index, &config->moves))
			return (false);
	}
	return (true);
}

static bool	get_target_index(t_stack *stack, size_t *ret)
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
