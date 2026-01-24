#include "libft.h"
#include "stack.h"
#include "lis_priv.h"
#include <stdlib.h>

typedef struct s_tail
{
	size_t	start;
	uint	*array;
	size_t	max_len;
	size_t	*pos;
	long	*prev;
}	t_tail;

static bool	compute_lis(t_lis *lis, const t_stack *stack, size_t start);
static bool	compute_tail(t_tail *tail, const t_stack *stack, size_t start);
static void	update_tail(t_tail *tail, uint value, size_t index);
static void	compute_swaps(t_lis *lis, const t_swaps *swaps);

bool	lis_best(t_lis *lis, const t_stack *stack, t_swaps *swaps)
{
	t_lis	current_lis;
	size_t	i;

	if (!compute_lis(lis, stack, 0))
		return (false);
	compute_swaps(lis, swaps);
	i = 1;
	while (i < stack->len)
	{
		if (!compute_lis(&current_lis, stack, i))
			return (lis_free(lis), false);
		compute_swaps(&current_lis, swaps);
		if (current_lis.keep_count < lis->keep_count)
			lis_free(&current_lis);
		else if (current_lis.keep_count > lis->keep_count || current_lis.swap_count < lis->swap_count)
		{
			lis_free(lis);
			*lis = current_lis;
		}
		else
			lis_free(&current_lis);
		i++;
	}
	return (true);
}

static bool	compute_lis(t_lis *lis, const t_stack *stack, size_t start)
{
	t_tail	tail;
	long	i;

	lis->start_index = start;
	lis->keep = malloc(stack->len * sizeof * lis->keep);
	if (!lis->keep)
		return (false);
	ft_memset(lis->keep, false, stack->len * sizeof * lis->keep);
	lis->swap = malloc(stack->len * sizeof * lis->swap);
	if (!lis->swap)
		return (free(lis->keep), false);
	ft_memset(lis->swap, false, stack->len * sizeof * lis->swap);
	lis->swap_count = 0;
	if (!compute_tail(&tail, stack, start))
		return (free(lis->keep), false);
	lis->keep_count = 0;
	i = (long)tail.pos[tail.max_len - 1];
	while (i != -1)
	{
		lis->keep[stack->data[i]] = true;
		lis->keep_count++;
		i = tail.prev[i];
	}
	return (free(tail.array), free(tail.pos), free(tail.prev), true);
}

static bool	compute_tail(t_tail *tail, const t_stack *stack, size_t start)
{
	size_t	i;
	size_t	index;

	tail->array = malloc(stack->len * sizeof * tail->array);
	if (!tail->array)
		return (false);
	tail->pos = malloc(stack->len * sizeof * tail->pos);
	if (!tail->pos)
		return (free(tail->array), false);
	tail->prev = malloc(stack->len * sizeof * tail->prev);
	if (!tail->prev)
		return (free(tail->array), free(tail->pos), false);
	ft_memset(tail->prev, -1, stack->len * sizeof * tail->prev);
	tail->start = start;
	tail->max_len = 0;
	i = 0;
	while (i < stack->len)
	{
		index = (start + i) % stack->len;
		update_tail(tail, stack->data[index], index);
		i++;
	}
	return (true);
}

static void	update_tail(t_tail *tail, uint value, size_t index)
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

static void	compute_swaps(t_lis *lis, const t_swaps *swaps)
{
	size_t	i;

	if (!swaps || swaps->count == 0)
		return ;
	i = 0;
	while (i < swaps->count)
	{
		if (lis->keep[swaps->from[i]] && lis->keep[swaps->to[i]])
		{
			lis->swap[swaps->from[i]] = true;
			lis->swap_count++;
		}
		i++;
	}
}
