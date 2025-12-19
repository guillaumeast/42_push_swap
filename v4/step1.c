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
	size_t	start_index;	// Real index of A at which LIS started
	size_t	capacity;		// max size (a->count)
	t_tail	tail;			// Uses virtual indexes
	int		*pos;			// Uses virtual indexes
	int		*prev;			// Uses virtual indexes
	bool	*keep;			// Use start_index value to convert virtual indexes to real ones (real_index = (virtual_index + start) % capacity)
	int		*logical_to_real_index;	// useless now => delete ?
}	t_lis;

static t_lis	*get_best_lis(t_stack *a);
static bool		build_lis(t_stack *a, t_lis *lis, size_t start_index);
static bool		init(t_lis *lis, size_t capacity);
static void		update(t_lis *lis, int value, int index);
static bool		lis_free(t_lis *lis);
static bool		should_swap(t_stack *a, bool *keep);
static void		print_lis(t_lis *lis, t_stack *a);

// TODO: après avoir build chaque LIS, simuler les swaps possibles pour calculer final_max_len et swap_cost pour calculer le score final (final_max_len - start - swap_cost)

bool	step_1(t_stack *a, t_stack *b)
{
	t_lis	*lis;
	int		i;
	int		real_index;

	lis = get_best_lis(a);
	if (!lis)
		return (false);
	i = lis->pos[lis->tail.max_len - 1];
	while (i != -1)
	{
		real_index = lis->logical_to_real_index[i];
		lis->keep[a->values[real_index]] = true;
		i = lis->prev[i];
	}
	print_lis(lis, a);
	i = 0;
	while (!is_sorted(a))
	{
		if (should_swap(a, lis->keep))
		{
			swap(a, b, A);
			if (is_sorted(a))
				break ;
			rotate(a, b, A);
			i++;
			if (is_sorted(a))
				break ;
			rotate(a, b, A);
			i += 2;
		}
		else if (lis->keep[a->values[0]])
		{
			rotate(a, b, A);
			i++;
		}
		else
		{
			push(a, b, B);
			i++;
		}
		debug_print(a, b);
	}
	lis_free(lis);
	return (true);
}

static t_lis	*get_best_lis(t_stack *a)
{
	t_lis	*lis;
	t_lis	*best_lis;
	size_t	start_index;
	int		score;
	int		best_score;

	best_lis = NULL;
	start_index = 0;
	while (start_index < a->count)
	{
		lis = malloc(sizeof *lis);
		if (!lis || !build_lis(a, lis, start_index))
		{
			if (best_lis)
				lis_free(best_lis);
			return (NULL);
		}
		// if (start_index < a->count / 2)
		// 	score = (int)(lis->tail.max_len - start_index);
		// else
		// 	score = (int)(lis->tail.max_len - (a->count - start_index));
		score = (int)lis->tail.max_len;
		if (!best_lis || score > best_score)
		{
			if (best_lis)
				lis_free(best_lis);
			best_lis = lis;
			best_score = score;
		}
		else
			lis_free(lis);
		start_index++;
	}
	return (best_lis);
}

static bool	build_lis(t_stack *a, t_lis *lis, size_t start_index)
{
	size_t	i;
	size_t	index;

	if (!init(lis, a->count))
		return (false);
	i = 0;
	while (i < a->count)
	{
		index = (start_index + i) % a->count;
		lis->logical_to_real_index[i] = (int)index;
		update(lis, a->values[index], (int)i);
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
	lis->logical_to_real_index = NULL;
	lis->tail.array = malloc(capacity * sizeof *lis->tail.array);
	lis->pos = malloc(capacity * sizeof *lis->pos);
	lis->prev = malloc(capacity * sizeof *lis->prev);
	lis->keep = malloc(capacity * sizeof *lis->keep);
	lis->logical_to_real_index = malloc(capacity * sizeof *lis->logical_to_real_index);
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
	if (lis->logical_to_real_index)
		free(lis->logical_to_real_index);
	free (lis);
	return (false);
}

static bool	should_swap(t_stack *a, bool *keep)
{
	int	current_value;
	int	next_value;
	int	second_next_value;

	if (a->count < 3)
		return (false);
	if (!keep[a->values[1]])
		return (false);
	current_value = a->values[0];
	next_value = a->values[1];
	second_next_value = a->values[2];
	if (current_value > next_value && current_value < second_next_value)
		return (true);
	return (false);
}

static void	print_lis(t_lis *lis, t_stack *a)
{
	int	i;

	if (!lis || !lis->keep)
		return ;
	i = 0;
	while ((size_t)i < a->count)
	{
		if (lis->keep[a->values[i]])
			printf("=> keep[%d] = %d\n", i, a->values[i]);
		i++;
	}
}
