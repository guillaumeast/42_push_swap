#include "libft.h"
#include "lis_priv.h"
#include <stdlib.h>

static bool	tail_init(t_tail *tail, size_t start_index, size_t capacity);
static void	tail_update(t_tail *tail, uint value, size_t index);

bool	tail_compute(t_tail *tail, t_stack *stack, size_t start_index)
{
	size_t	i;
	size_t	index;

	if (!tail_init(tail, start_index, stack->len))
		return (false);
	i = 0;
	while (i < stack->len)
	{
		index = (start_index + i) % stack->len;
		tail_update(tail, stack->data[index], index);
		i++;
	}
	return (tail);
}

static bool	tail_init(t_tail *tail, size_t start_index, size_t capacity)
{
	tail->start_index = start_index;
	tail->array = NULL;
	tail->pos = NULL;
	tail->prev = NULL;
	tail->array = malloc(capacity * sizeof * tail->array);
	tail->pos = malloc(capacity * sizeof * tail->pos);
	tail->prev = malloc(capacity * sizeof * tail->prev);
	if (!tail->array || !tail->pos || !tail->prev)
	{
		tail_free(tail);
		return (false);
	}
	ft_memset(tail->pos, -1, capacity * sizeof * tail->pos);
	ft_memset(tail->prev, -1, capacity * sizeof * tail->prev);
	tail->max_len = 0;
	return (tail);
}

static void	tail_update(t_tail *tail, uint value, size_t index)
{
	size_t	lower_index;
	int		left;
	int		mid;
	int		right;

	left = 0;
	right = (int)tail->max_len;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (tail->array[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	lower_index = (size_t)left;
	tail->array[lower_index] = value;
	if (lower_index == tail->max_len)
		tail->max_len++;
	tail->pos[lower_index] = index;
	if (lower_index > 0)
		tail->prev[index] = (long)tail->pos[lower_index - 1];
	else
		tail->prev[index] = -1;
}

void	tail_free(t_tail *tail)
{
	if (tail->array)
		free(tail->array);
	if (tail->pos)
		free(tail->pos);
	if (tail->prev)
		free(tail->prev);
}
