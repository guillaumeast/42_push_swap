#include "config.h"
#include "stack.h"
#include "push.h"
#include "greedy.h"
#include "finish.h"

bool	config_init(t_stack *a, t_stack *b, t_config *ret)
{
	if (!stack_dup(&ret->a, a))
		return (false);
	if (!stack_dup(&ret->b, b))
		return (stack_free(&ret->a), false);
	if (!buff_init(&ret->moves, (a->len + b->len) * 12))
		return (config_free(ret), false);
	ret->step_1 = NONE;
	ret->step_2 = NONE;
	ret->swap = false;
	ret->error = false;
	return (true);
}

bool	config_run(t_config *config)
{
	if (config->step_1 == NAIVE)
		if (!push_to_b(config))
			return (false);
	if (config->step_2 == GREEDY)
		if (!greedy(config))
			return (false);
	if (!stack_is_sorted(&config->a))
	{
		config->error = true;
		return (true);
	}
	return (finish(config));
}

void	config_free(t_config *config)
{
	stack_free(&config->a);
	stack_free(&config->b);
	buff_free(&config->moves);
}
