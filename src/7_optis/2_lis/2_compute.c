#include "libft.h"
#include "stack.h"
#include "lis_priv.h"
#include <stdlib.h>
# include "debug.h"

typedef struct s_tail
{
	size_t	start;
	uint	*array;
	size_t	max_len;
	size_t	*pos;
	long	*prev;
}	t_tail;

static bool	compute_tail(t_tail *tail, const t_stack *stack, size_t start);
static void	update_tail(t_tail *tail, uint value, size_t index);
static void	compute_swaps(t_lis *lis, const t_swaps *swaps);

// i = start_index
bool	get_lis(t_lis *lis, const t_stack *stk, size_t i, const t_swaps *swaps)
{
	t_tail	tail;
	long	index;

	lis->start_index = i;
	lis->keep = malloc(stk->len * sizeof * lis->keep);
	if (!lis->keep)
		return (false);
	ft_memset(lis->keep, false, stk->len * sizeof * lis->keep);
	lis->swap = malloc(stk->len * sizeof * lis->swap);
	if (!lis->swap)
		return (free(lis->keep), false);
	ft_memset(lis->swap, false, stk->len * sizeof * lis->swap);
	lis->swap_count = 0;
	if (!compute_tail(&tail, stk, i))
		return (free(lis->keep), false);
	lis->keep_count = 0;
	index = (long)tail.pos[tail.max_len - 1];
	while (index != -1)
	{
		lis->keep[stk->data[index]] = true;
		lis->keep_count++;
		index = tail.prev[index];
	}
	compute_swaps(lis, swaps);
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

void	lis_free(t_lis *lis)
{
	if (lis->keep)
		free(lis->keep);
	if (lis->swap)
		free(lis->swap);
}
