#include "push_swap.h"
#include <limits.h>

static size_t	get_target_index(t_stack *b, int a_value);
static void		push_to_b(t_stack *a, t_stack *b);
static void		rotate_and_push_from_b(t_lis *lis, t_stack *a, t_stack *b);

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
			lis->keep[a->values[1]] = true;
			if (!is_sorted(a))
				rotate_and_push_from_b(lis, a, b);
			if (!is_sorted(a))
				rotate_and_push_from_b(lis, a, b);
		}
		else if (lis->keep[a->values[0]])
			rotate_and_push_from_b(lis, a, b);
		else
			push_to_b(a, b);
		// debug_print(a, b);
	}
	lis_free(&lis);
	return (true);
}

// Keep B sorted (from MAX to MIN) while pushing to it
static void	push_to_b(t_stack *a, t_stack *b)
{
	size_t	target_index;

	target_index = get_target_index(b, a->values[0]);
	if (target_index <= b->count / 2)
	{
		while (target_index > 0)
		{
			rotate(a, b, B);
			target_index--;
		}
	}
	else
	{
		while (b->count - target_index > 0)
		{
			rotate_reverse(a, b, B);
			target_index++;
		}
	}
	push(a, b, B);
}

// Returns the index of the biggest value in B which is smaller than a_value.
// If it doesn't exists, it returns the index of the biggest value in B.
// If B contains 0 or 1 value, it returns 0 (a_value can be push directly to B).
static size_t	get_target_index(t_stack *b, int a_value)
{
	size_t	i;
	int		target_index;
	int		target_value;
	int		biggest_index;
	int		biggest_value;

	if (b->count < 2)
		return (0);
	target_index = -1;
	target_value = -1;
	biggest_index = -1;
	i = 0;
	while (i < b->count)
	{
		if (biggest_index == -1 || b->values[i] >= biggest_value)
		{
			biggest_index = (int)i;
			biggest_value = b->values[i];
		}
		if (b->values[i] < a_value && b->values[i] >= target_value)
		{
			target_index = (int)i;
			target_value = b->values[i];
		}
		i++;
	}
	if (target_index != -1)
		return ((size_t)target_index);
	return ((size_t)biggest_index);
}

// TODO: gérer le cas où previous = max(A) et next = min(A) (en considérant uniquement les keep)
static void	rotate_and_push_from_b(t_lis *lis, t_stack *a, t_stack *b)
{
	int		previous;
	int		next;
	size_t	i;
	int		b_target_value;
	int		b_target_index;
	size_t	push_count;

	previous = a->values[0];
	next = a->values[0];
	i = 1;
	while (i < a->count)
	{
		if (lis->keep[a->values[i]])
		{
			next = a->values[i];
			break ;
		}
		i++;
	}
	rotate(a, b, A);
	if (next > previous)
	{
		if (next - previous < 2)
			return ;
		b_target_index = -1;
		b_target_value = -1;
		i = 0;
		while (i < b->count)
		{
			if (b->values[i] > previous && b->values[i] < next && b->values[i] > b_target_value)
			{
				b_target_value = b->values[i];
				b_target_index = (int)i;
			}
			i++;
		}
		if (b_target_index == -1)
			return ;
		if (b_target_index <= (int)b->count / 2)
		{
			while (b_target_index > 0)
			{
				rotate(a, b, B);
				b_target_index--;
			}
		}
		else
		{
			while ((int)b->count - b_target_index > 0)
			{
				rotate_reverse(a, b, B);
				b_target_index++;
			}
		}
		push_count = 0;
		while (b->count > 0 && b->values[0] < next)
		{
			push(a, b, A);
			push_count++;
		}
		while (push_count > 0)
		{
			rotate(a, b, A);
			push_count--;
		}
	}
	else
	{
		b_target_index = -1;
		b_target_value = -1;
		i = 0;
		while (i < b->count)
		{
			if ((b->values[i] > previous || b->values[i] < next)
				&& (b_target_index == -1 || b->values[i] > b_target_value))
			{
				b_target_value = b->values[i];
				b_target_index = (int)i;
			}
			i++;
		}
		if (b_target_index == -1)
			return ;
		if (b_target_index <= (int)b->count / 2)
		{
			while (b_target_index > 0)
			{
				rotate(a, b, B);
				b_target_index--;
			}
		}
		else
		{
			while ((int)b->count - b_target_index > 0)
			{
				rotate_reverse(a, b, B);
				b_target_index++;
			}
		}
		push_count = 0;
		while (b->count > 0
			&& (b->values[0] > previous || b->values[0] < next))
		{
			push(a, b, A);
			push_count++;
		}
		while (push_count > 0)
		{
			rotate(a, b, A);
			push_count--;
		}
	}
}

// // TODO: 0 et MAX doivent être insérés au-dessus de min(A) !
// static void	push_from_b_and_rotate(t_stack *a, t_stack *b)
// {
// 	size_t	i;
// 	int		target_index;
// 	int		target_value;
// 	int		first_pushed_value;

// 	target_index = -1;
// 	target_value = -1;
// 	i = 0;
// 	// TODO: if A[0] == min(A) => [insert 0 from B] + [insert all B values > max(A)]
// 	while (i < b->count)
// 	{
// 		if (b->values[i] > a->values[a->count - 1] && b->values[i] < a->values[0] && b->values[i] > target_value)
// 		{
// 			target_index = (int)i;
// 			target_value = b->values[i];
// 		}
// 		i++;
// 	}
// 	if (target_index != -1)
// 	{
// 		if (target_index <= (int)b->count / 2)
// 		{
// 			while (b->values[0] != target_value)
// 				rotate(a, b, B);
// 		}
// 		else
// 		{
// 			while (b->values[0] != target_value)
// 				rotate_reverse(a, b, B);
// 		}
// 		first_pushed_value = -1;
// 		while (b->values[0] < a->values[0])
// 		{
// 			if (first_pushed_value == -1)
// 				first_pushed_value = b->values[0];
// 			push(a, b, A);
// 		}
// 		while (first_pushed_value != -1 && a->values[0] <= first_pushed_value)
// 			rotate(a, b, A);
// 	}
// 	rotate(a, b, A);
// }

// static void	push_to_b(t_stack *a, t_stack *b)
// {
// 	int	i;
// 	int	target_index;
// 	int	target_value;
// 	int	max_index;
// 	int	max_value;

// 	if (b->count > 0)
// 	{
// 		i = 0;
// 		target_index = -1;
// 		target_value = -1;
// 		max_index = -1;
// 		max_value = -1;
// 		while (i < (int)b->count)
// 		{
// 			if (b->values[i] > target_value && b->values[i] < a->values[0])
// 			{
// 				target_index = i;
// 				target_value = b->values[i];
// 			}
// 			if (max_index == -1 || b->values[i] > max_value)
// 			{
// 				max_index = i;
// 				max_value = b->values[i];
// 			}
// 			i++;
// 		}
// 		// Target not found => A[0] = min(B) => put it at the bottom of B
// 		if (target_value == -1 && max_index <= (int)b->count / 2)
// 		{
// 			while (b->values[0] != max_value)
// 			{
// 				fprintf(stderr, "[4] max_index    = %i (%i)\n", max_index, max_value);
// 				rotate(a, b, B);
// 			}
// 		}
// 		else if (target_value == -1)
// 		{
// 			while (b->values[0] != max_value)
// 			{
// 				fprintf(stderr, "[5] max_index    = %i (%i)\n", max_index, max_value);
// 				rotate_reverse(a, b, B);
// 			}
// 		}
// 		else if (target_index <= (int)b->count / 2)
// 		{
// 			while (b->values[0] != target_value)
// 			{
// 				fprintf(stderr, "[6] target_index = %i (%i)\n", target_index, target_value);
// 				debug_print(a, b);
// 				rotate(a, b, B);
// 			}
// 		}
// 		else
// 		{
// 			while (b->values[0] != target_value)
// 			{
// 				fprintf(stderr, "[7] target_index = %i (%i)\n", target_index, target_value);
// 				debug_print(a, b);
// 				rotate_reverse(a, b, B);
// 			}
// 		}
// 	}
// 	push(a, b, B);
// }
