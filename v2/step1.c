#include "push_swap.h"

static bool	should_insert_from_b(t_stack *a, t_stack *b, size_t index);
static bool	should_swap(t_stack *a, size_t index);
static bool	value_is_sorted(t_stack *a, size_t index);

bool	step_1(t_stack *a, t_stack *b)
{
	int	first_kept_value;

	first_kept_value = -1;
	while (!is_sorted(a) && a->values[0] != first_kept_value)
	{
		if (should_swap(a, 0))
			swap(a, b, A);
		else if (should_insert_from_b(a, b, 0))
			push(a, b, A);
		else if (value_is_sorted(a, 0))
		{
			if (first_kept_value == -1)
				first_kept_value = a->values[0];
			rotate(a, b, A);
		}
		else
		{
			push(a, b, B);
			if (b->count > 0 && b->values[0] < b->values[1])
				rotate(a, b, B);
		}
		debug_print(a, b);
	}
	debug_print_move_count();
	return (true);
}

static bool	should_insert_from_b(t_stack *a, t_stack *b, size_t index)
{
	int	previous_value;
	int	current_value;

	if (b->count == 0)
		return (false);
	if (index == 0)
		previous_value = a->values[a->count - 1];
	else
		previous_value = a->values[index - 1];
	current_value = a->values[index];
	return (b->values[0] > previous_value && b->values[0] < current_value);
}

static bool	should_swap(t_stack *a, size_t index)
{
	int	current_value;
	int	next_value;
	int	second_next_value;

	if (a->count < 3)
		return (false);
	current_value = a->values[index % a->count];
	next_value = a->values[(index + 1) % a->count];
	second_next_value = a->values[(index + 2) % a->count];
	if (current_value > next_value && current_value < second_next_value)
		return (true);
	return (false);
}

static bool	value_is_sorted(t_stack *a, size_t index)
{
	size_t	previous_index;
	size_t	target_index;
	int		previous_value;
	int		current_value;

	if (a->count < 3)
		return (true);
	if (index == 0)
		previous_index = a->count - 1;
	else
		previous_index = (index - 1) % a->count;
	target_index = index % a->count;
	previous_value = a->values[previous_index];
	current_value = a->values[target_index];
	if (current_value == 0)
		return (true);
	return (previous_value < current_value);
}
