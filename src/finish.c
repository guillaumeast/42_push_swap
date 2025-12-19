#include "push_swap.h"

bool	is_sorted(t_stack *stack)
{
	size_t	i;
	int		breaks;

	breaks = 0;
	i = 0;
	while (i < stack->count)
	{
		if (stack->values[i] > stack->values[(i + 1) % stack->count])
			breaks++;
		i++;
	}
	return (breaks <= 1);
}

bool	finish(t_stack *a, t_stack *b)
{
	size_t	zero_index;

	if (b->count > 0 || !is_sorted(a))
		return (false);
	zero_index = 0;
	while (a->values[zero_index] != 0)
		zero_index++;
	if (zero_index <= a->count / 2)
	{
		while (a->values[0] != 0)
			rotate(a, b, A);
	}
	else
	{
		while (a->values[0] != 0)
			rotate_reverse(a, b, A);
	}
	return (true);
}
