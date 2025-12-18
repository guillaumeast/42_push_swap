#include "push_swap.h"

static void	rebuild_from_b_to_a(t_stack *a, t_stack *b);
static void	compute_indexes(t_stack *stack, int *max_i, int *second_max_i);
static int	get_cost(t_stack *stack, int index);
static void	rebuild_index(t_stack *a, t_stack *b, size_t index);

void	step_2(t_stack *a, t_stack *b)
{
	rebuild_from_b_to_a(a, b);
}

static void	rebuild_from_b_to_a(t_stack *a, t_stack *b)
{
	int		max_index;
	int		second_max_index;
	int		max_cost;
	int		second_max_cost;
	bool	swap_next;

	swap_next = false;
	while (b->count > 0)
	{
		compute_indexes(b, &max_index, &second_max_index);
		max_cost = get_cost(b, max_index);
		second_max_cost = get_cost(b, second_max_index);
		if (swap_next || second_max_cost == -1 || max_cost < second_max_cost)
		{
			rebuild_index(a, b, (size_t)max_index);
			if (swap_next)
				swap(a, b, A);
			swap_next = false;
		}
		else
		{
			rebuild_index(a, b, (size_t)second_max_index);
			swap_next = true;
		}
	}
}

static void	compute_indexes(t_stack *stack, int *max_i, int *second_max_i)
{
	size_t	i;

	i = 0;
	*max_i = -1;
	*second_max_i = -1;
	while (i < stack->count)
	{
		if (*max_i == -1 || stack->values[i] > stack->values[*max_i])
		{
			*second_max_i = *max_i;
			*max_i = (int)i;
		}
		i++;
	}
}

static int	get_cost(t_stack *stack, int index)
{
	int	cost_from_top;
	int	cost_from_bottom;

	if (index == -1)
		return (-1);
	cost_from_top = index;
	cost_from_bottom = (int)stack->count - index;
	if (cost_from_top <= cost_from_bottom)
		return (cost_from_top);
	return (cost_from_bottom);
}

static void	rebuild_index(t_stack *a, t_stack *b, size_t index)
{
	if (index <= b->count / 2)
	{
		while (index--)
			rotate(a, b, B);
	}
	else
	{
		while (index++ < b->count)
			rotate_reverse(a, b, B);
	}
	push(a, b, A);
}
