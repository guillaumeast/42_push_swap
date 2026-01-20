#include "libft.h"
#include "lis.h"
#include "lis_priv.h"
#include <stdlib.h>

static bool	lis_compute(t_lis *lis, t_stack *stack, size_t start_index);
static bool	lis_init(t_lis *lis, t_tail *tail, t_stack *stack);
static void	lis_compute_swaps(t_lis *lis, t_stack *stack, size_t index);

bool	lis_compute_best(t_stack *stack, t_lis *lis)
{
	size_t	start_index;
	t_lis	tmp_lis;
	size_t	max_len;

	max_len = 0;
	start_index = 0;
	lis->keep = NULL;
	lis->swap = NULL;
	while (start_index < stack->len)
	{
		if (!lis_compute(&tmp_lis, stack, start_index))
			return (false);
		else if (tmp_lis.final_len > max_len)
		{
			lis_free(lis);
			*lis = tmp_lis;
			max_len = tmp_lis.final_len;
		}
		else
			lis_free(&tmp_lis);
		start_index++;
	}
	return (true);
}

static bool	lis_compute(t_lis *lis, t_stack *stack, size_t start_index)
{
	t_tail	tail;
	long	index;

	if (!tail_compute(&tail, stack, start_index))
		return (false);
	if (!lis_init(lis, &tail, stack))
		return (false);
	index = (long)tail.pos[tail.max_len - 1];
	while (index != -1)
	{
		lis->keep[stack->data[index]] = true;
		lis->keep_count++;
		index = tail.prev[index];
	}
	index = 0;
	while (index < (long)stack->len)
	{
		lis_compute_swaps(lis, stack, (size_t)index);
		index++;
	}
	lis->final_len = lis->keep_count + lis->swap_count;
	return (true);
}

static bool	lis_init(t_lis *lis, t_tail *tail, t_stack *stack)
{
	lis->keep = malloc(stack->len * sizeof * lis->keep);
	lis->swap = malloc(stack->len * sizeof * lis->keep);
	if (!lis->keep || !lis->swap)
		return (lis_free(lis), false);
	ft_memset(lis->keep, false, stack->len * sizeof * lis->keep);
	ft_memset(lis->swap, false, stack->len * sizeof * lis->swap);
	lis->keep_count = 0;
	lis->swap_count = 0;
	lis->final_len = 0;
	lis->start_index = tail->start_index;
	return (true);
}

static void	lis_compute_swaps(t_lis *lis, t_stack *stack, size_t index)
{
	size_t	next_kept_i;
	uint	current;
	uint	next;
	uint	second_next;

	current = stack->data[index];
	next = stack->data[(index + 1) % stack->len];
	if (lis->keep[current] || !lis->keep[next])
		return ;
	next_kept_i = (index + 2) % stack->len;
	while (next_kept_i != index && !lis->keep[stack->data[next_kept_i]])
		next_kept_i = (next_kept_i + 1) % stack->len;
	if (next_kept_i == index)
		return ;
	second_next = stack->data[next_kept_i];
	if (current > next && (current < second_next || second_next == 0))
	{
		lis->swap[current] = true;
		lis->keep[current] = true;
		lis->swap_count++;
	}
}

void	lis_free(t_lis *lis)
{
	if (lis->keep)
		free(lis->keep);
	if (lis->swap)
		free(lis->swap);
}
