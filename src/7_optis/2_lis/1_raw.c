#include "libft.h"
#include "lis_priv.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

typedef struct s_tail
{
	size_t	start_index;
	uint	*array;
	size_t	max_len;
	size_t	*pos;
	long	*prev;
}	t_tail;

static bool	compute_tail(t_tail *tail, t_stack *stack, size_t start_index);
static void	update_tail(t_tail *tail, uint value, size_t index);
static void	normalize_swaps(t_stack *stack, t_lis *lis);
static void	free_tail(t_tail *tail);

/*
*	Computes a single lis from a stack, starting at the given index.
*
*	@note: swaps is optional.
*	@note: swaps is borrowed (lis creates its own copy of it).
*/
bool	lis_compute(t_lis *lis, t_stack *stack, bool *swaps, size_t start_index)
{
	t_tail	tail;
	long	i;

	// fprintf(stderr, "[🔦 DEBUG] ======> lis_compute() from index [%zu]...\n", start_index);	// TMP: remove before submit
	lis->start_index = start_index;
	lis->keep = malloc(stack->len * sizeof * lis->keep);
	if (!lis->keep)
		return (false);
	ft_memset(lis->keep, false, stack->len * sizeof * lis->keep);
	lis->swap = NULL;
	if (swaps)
	{
		lis->swap = malloc(stack->len * sizeof * lis->swap);
		if (!lis->swap)
			return (lis_free(lis), false);
		ft_memcpy(lis->swap, swaps, stack->len * sizeof * lis->swap);
	}
	if (!compute_tail(&tail, stack, start_index))
		return (lis_free(lis), false);
	lis->keep_count = 0;
	i = (long)tail.pos[tail.max_len - 1];
	while (i != -1)
	{
		lis->keep[stack->data[i]] = true;
		lis->keep_count++;
		i = tail.prev[i];
	}
	if (swaps)
		normalize_swaps(stack, lis);
	free_tail(&tail);
	// lis_print(lis, stack->len);	// TMP: remove before submit
	return (true);
}

static bool	compute_tail(t_tail *tail, t_stack *stack, size_t start_index)
{
	size_t	i;
	size_t	index;

	tail->array = malloc(stack->len * sizeof * tail->array);
	tail->pos = malloc(stack->len * sizeof * tail->pos);
	tail->prev = malloc(stack->len * sizeof * tail->prev);
	if (!tail->array || !tail->pos || !tail->prev)
		return (free_tail(tail), false);
	ft_memset(tail->prev, -1, stack->len * sizeof * tail->prev);
	tail->start_index = start_index;
	tail->max_len = 0;
	i = 0;
	while (i < stack->len)
	{
		index = (start_index + i) % stack->len;
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

static void	normalize_swaps(t_stack *stack, t_lis *lis)
{
	size_t	i;
	uint	current;
	uint	prev;

	// fprintf(stderr, "[🔦 DEBUG] ======> normalize_swaps()...\n");	// TMP: remove before submit
	lis->swap_count = 0;
	i = 0;
	if (stack->len > 2 && lis->swap[stack->data[0]] && lis->swap[stack->data[1]] && 
		lis->keep[stack->data[stack->len - 1]] && lis->keep[stack->data[1]])
	{
		if (!lis->swap[stack->data[0]])
			1 && (lis->swap[stack->data[0]] = true, lis->swap_count++);
		if (lis->keep[stack->data[0]] && !lis->swap[stack->data[1]])
			1 && (lis->swap[stack->data[1]] = true, lis->swap_count++);
		i = 2;
	}
	while (i < stack->len)
	{
		prev = stack_get_value(stack, (long)i - 1);
		current = stack_get_value(stack, (long)i);
		// fprintf(stderr, "           prev = %u | current = %u | swap[%u] = %i\n", prev, current, current, lis->swap[current]);
		if (lis->swap[current] && (!lis->keep[current] || !lis->keep[prev]))
			lis->swap[current] = false;
		else if (lis->swap[current])
			lis->swap_count++;
		// fprintf(stderr, "           => swap[%u] = %i\n", current, lis->swap[current]);
		i++;
	}
	// fprintf(stderr, "           normalize_swaps() done!\n");
}

static void	free_tail(t_tail *tail)
{
	if (tail->array)
		free(tail->array);
	if (tail->pos)
		free(tail->pos);
	if (tail->prev)
		free(tail->prev);
}
