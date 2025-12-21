#include "v4.h"
#include "push_swap.h"

bool	step_1(t_stack *a, t_stack *b)
{
	t_lis	*lis;

	lis = lis_get_best(a);
	if (!lis)
		return (false);
	while (!is_sorted(a))
	{
		if (lis->swap[a->values[0]])
		{
			swap(a, b, A);
			debug_print(a, b);
			if (is_sorted(a))
				break ;
			rotate(a, b, A);
			debug_print(a, b);
			if (is_sorted(a))
				break ;
			rotate(a, b, A);
		}
		else if (lis->keep[a->values[0]])
			rotate(a, b, A);
		else
			push(a, b, B);
		debug_print(a, b);
	}
	lis_free(&lis);
	return (true);
}
