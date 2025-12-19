#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>

typedef struct s_tail
{
	int		*array;
	size_t	max_len;
}	t_tail;

typedef struct s_lis
{
	t_tail	tail;
	int		*pos;
	int		*prev;
	bool	*keep;
}	t_lis;

static bool	build_lis(t_stack *a, t_lis *lis);
static bool	init(t_lis *lis, size_t capacity);
static void	update(t_lis *lis, int value, int index);
static bool	lis_free(t_lis *lis);
static bool	should_swap(t_stack *a);

// TODO: LIS circulaire (boucle en % a->count) à partir de chaque index possible puis garder uniquement la best lis

bool	step_1(t_stack *a, t_stack *b)
{
	t_lis	lis;
	int		i;
	int		to_process;

	if (!build_lis(a, &lis))
		return (false);
	i = lis.pos[lis.tail.max_len - 1];
	while (i != -1)
	{
		lis.keep[a->values[i]] = true;
		i = lis.prev[i];
	}
	to_process = (int)a->count;
	i = 0;
	while (i < to_process)
	{
		if (lis.keep[a->values[1]] && should_swap(a))
		{
			swap(a, b, A);
			rotate(a, b, A);
			i++;
			rotate(a, b, A);
		}
		else if (lis.keep[a->values[0]])
			rotate(a, b, A);
		else
			push(a, b, B);
		i++;
	}
	lis_free(&lis);
	return (true);
}

static bool	build_lis(t_stack *a, t_lis *lis)
{
	size_t	i;

	if (!init(lis, a->count))
		return (false);
	i = 0;
	while (i < a->count)
	{
		update(lis, a->values[i], (int)i);
		i++;
	}
	return (true);
}

static bool	init(t_lis *lis, size_t capacity)
{
	lis->tail.array = NULL;
	lis->pos = NULL;
	lis->prev = NULL;
	lis->keep = NULL;
	lis->tail.array = malloc(capacity * sizeof *lis->tail.array);
	lis->pos = malloc(capacity * sizeof *lis->pos);
	lis->prev = malloc(capacity * sizeof *lis->prev);
	lis->keep = malloc(capacity * sizeof *lis->keep);
	if (!lis->tail.array || !lis->pos || !lis->prev || !lis->keep)
		return (lis_free(lis));
	ft_memset(lis->prev, -1, capacity * sizeof *lis->prev);
	ft_memset(lis->keep, false, capacity * sizeof *lis->keep);
	lis->tail.max_len = 0;
	return (true);
}

static void	update(t_lis *lis, int value, int index)
{
	size_t	lower_index;
	int 	left;
	int		mid;
	int		right;

	left = 0;
	right = (int)lis->tail.max_len;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (lis->tail.array[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	lower_index = (size_t)left;
	lis->tail.array[lower_index] = value;
	if (lower_index == lis->tail.max_len)
		lis->tail.max_len++;
	lis->pos[lower_index] = index;
	if (lower_index > 0)
		lis->prev[index] = lis->pos[lower_index - 1];
	else
		lis->prev[index] = -1;
}

static bool	lis_free(t_lis *lis)
{
	if (lis->tail.array)
		free(lis->tail.array);
	if (lis->pos)
		free(lis->pos);
	if (lis->prev)
		free(lis->prev);
	if (lis->keep)
		free(lis->keep);
	return (false);
}

static bool	should_swap(t_stack *a)
{
	int	current_value;
	int	next_value;
	int	second_next_value;

	if (a->count < 3)
		return (false);
	current_value = a->values[0];
	next_value = a->values[1];
	second_next_value = a->values[2];
	if (current_value > next_value && current_value < second_next_value)
		return (true);
	return (false);
}
