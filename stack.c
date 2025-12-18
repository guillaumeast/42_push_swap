#include "push_swap.h"
#include <stdlib.h>

static int	get_index(int value, const int *array, size_t size);

bool	stack_init(t_stack *a, t_stack *b, size_t capacity)
{
	a->cap = capacity;
	b->cap = capacity;
	a->count = 0;
	b->count = 0;
	a->values = malloc(capacity * sizeof *a->values);
	b->values = malloc(capacity * sizeof *a->values);
	return (a->values && b->values);
}

bool	stack_convert_to_sorted_indexes(t_stack *a)
{
	int		*array;
	size_t	i;

	array = malloc(a->cap * sizeof *array);
	if (!array)
		return (false);
	i = 0;
	while (i < a->cap)
	{
		array[i] = a->values[i];
		i++;
	}
	if (!sort(&array, a->cap))
		return (free(array), false);
	i = 0;
	while (i < a->cap)
	{
		a->values[i] = get_index(a->values[i], array, a->cap);
		if (a->values[i] == -1)
			return (free(array), false);
		i++;
	}
	free(array);
	return (true);
}

static int	get_index(int value, const int *array, size_t size)
{
	size_t	low;
	size_t	mid;
	size_t	high;

	low = 0;
	high = size - 1;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (array[mid] == value)
			return ((int)mid);
		else if (array[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (-1);
}

void	stack_free(t_stack *a, t_stack *b)
{
	if (a->values)
		free(a->values);
	if (b->values)
		free(b->values);
}
