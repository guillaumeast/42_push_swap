#include "push_swap.h"

// bool	step_1(t_stack *a, t_stack *b)
// {
// 	while (a->count > 2)
// 		push(a, b, B);
// 	return (true);
// }

static void	optimized_swap(t_stack *a, t_stack *b, int *b_min, int *b_max);
static void	optimized_rotate(t_stack *a, t_stack *b, int *b_min, int *b_max);
static void	push_and_update(t_stack *a, t_stack *b, int *b_min, int *b_max);

bool	step_1(t_stack *a, t_stack *b)
{
	int		b_min;
	int		b_max;
	t_lis	*lis;

	b_min = -1;
	b_max = -1;
	lis = lis_get_best(a);
	if (!lis)
		return (false);
	while (!is_sorted(a))
	{
		if (lis->swap[a->values[0]])
			optimized_swap(a, b, &b_min, &b_max);
		else if (lis->keep[a->values[0]])
			optimized_rotate(a, b, &b_min, &b_max);
		else
			push_and_update(a, b, &b_min, &b_max);
	}
	lis_free(&lis);
	return (true);
}

static void	optimized_swap(t_stack *a, t_stack *b, int *b_min, int *b_max)
{
	if (b->count > 0 && b->values[0] < b->values[1])
		swap(a, b, BOTH);
	else
		swap(a, b, A);
	if (!is_sorted(a))
		optimized_rotate(a, b, b_min, b_max);
	if (!is_sorted(a))
		optimized_rotate(a, b, b_min, b_max);
}

static void	optimized_rotate(t_stack *a, t_stack *b, int *b_min, int *b_max)
{
	int	median;

	median = (*b_min + *b_max) / 2;
	if (b->count > 0 && b->values[0] < median)
		rotate(a, b, BOTH);
	else
		rotate(a, b, A);
}

static void	push_and_update(t_stack *a, t_stack *b, int *b_min, int *b_max)
{
	push(a, b, B);
	if (*b_min == -1 || b->values[0] < *b_min)
		*b_min = b->values[0];
	if (*b_max == -1 || b->values[0] > *b_max)
		*b_max = b->values[0];
}
