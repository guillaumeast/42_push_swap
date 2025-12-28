#include "push_swap.h"
#include <limits.h>

// bool	step_1(t_stack *a, t_stack *b)
// {
// 	while (a->count > 2)
// 		push(a, b, B);
// 	return (true);
// }

static void	push_to_b(t_stack *a, t_stack *b);
static void	push_from_b_and_rotate(t_stack *a, t_stack *b);

/*
*	V5
*	Always keep B sorted
*	Insert from B to A as soon as possible (to keep B small)
*	Keep track of each stack min and max to make pushes easier
*	Min and max always insert on top of min value
*/

// TODO: optimize RA + RB = RR (before RA -> search for next B value to be inserted, if RB needed, RR instead of RA)

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
			if (!is_sorted(a))
				push_from_b_and_rotate(a, b);
			if (!is_sorted(a))
				push_from_b_and_rotate(a, b);
		}
		else if (lis->keep[a->values[0]])
			push_from_b_and_rotate(a, b);
		else
			push_to_b(a, b);
	}
	lis_free(&lis);
	return (true);
}

// TODO: 0 et MAX doivent être insérés au-dessus de min(A) !
static void	push_from_b_and_rotate(t_stack *a, t_stack *b)
{
	size_t	i;
	int		target_index;
	int		target_value;
	int		first_pushed_value;

	target_index = -1;
	target_value = -1;
	i = 0;
	// TODO: if A[0] == min(A) => [insert 0 from B] + [insert all B values > max(A)]
	while (i < b->count)
	{
		if (b->values[i] > a->values[a->count - 1] && b->values[i] < a->values[0] && b->values[i] > target_value)
		{
			target_index = (int)i;
			target_value = b->values[i];
		}
		i++;
	}
	if (target_index != -1)
	{
		if (target_index <= (int)b->count / 2)
		{
			while (b->values[0] != target_value)
			{
				fprintf(stderr, "[1] target_index = %i (%i)\n", target_index, target_value);
				debug_print(a, b);
				rotate(a, b, B);
			}
		}
		else
		{
			while (b->values[0] != target_value)
			{
				fprintf(stderr, "[2] target_index = %i (%i)\n", target_index, target_value);
				debug_print(a, b);
				rotate_reverse(a, b, B);
			}
		}
		first_pushed_value = -1;
		while (b->values[0] < a->values[0])
		{
			if (first_pushed_value == -1)
				first_pushed_value = b->values[0];
			push(a, b, A);
		}
		while (first_pushed_value != -1 && a->values[0] <= first_pushed_value)
		{
			fprintf(stderr, "[3] first_pushed_value = %i\n", first_pushed_value);
			debug_print(a, b);
			rotate(a, b, A);
		}
	}
	rotate(a, b, A);
}

static void	push_to_b(t_stack *a, t_stack *b)
{
	int	i;
	int	target_index;
	int	target_value;
	int	max_index;
	int	max_value;

	if (b->count > 0)
	{
		i = 0;
		target_index = -1;
		target_value = -1;
		max_index = -1;
		max_value = -1;
		while (i < (int)b->count)
		{
			if (b->values[i] > target_value && b->values[i] < a->values[0])
			{
				target_index = i;
				target_value = b->values[i];
			}
			if (max_index == -1 || b->values[i] > max_value)
			{
				max_index = i;
				max_value = b->values[i];
			}
			i++;
		}
		// Target not found => A[0] = min(B) => put it at the bottom of B
		if (target_value == -1 && max_index <= (int)b->count / 2)
		{
			while (b->values[0] != max_value)
			{
				fprintf(stderr, "[4] max_index    = %i (%i)\n", max_index, max_value);
				rotate(a, b, B);
			}
		}
		else if (target_value == -1)
		{
			while (b->values[0] != max_value)
			{
				fprintf(stderr, "[5] max_index    = %i (%i)\n", max_index, max_value);
				rotate_reverse(a, b, B);
			}
		}
		else if (target_index <= (int)b->count / 2)
		{
			while (b->values[0] != target_value)
			{
				fprintf(stderr, "[6] target_index = %i (%i)\n", target_index, target_value);
				debug_print(a, b);
				rotate(a, b, B);
			}
		}
		else
		{
			while (b->values[0] != target_value)
			{
				fprintf(stderr, "[7] target_index = %i (%i)\n", target_index, target_value);
				debug_print(a, b);
				rotate_reverse(a, b, B);
			}
		}
	}
	push(a, b, B);
}
