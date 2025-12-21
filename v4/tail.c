#include "libft.h"
#include "v4.h"
#include <stdlib.h>

static t_tail	*tail_new(size_t start_index, size_t capacity);
static void		tail_update(t_tail *tail, int value, int index);
// static void		tail_print(t_tail *tail, size_t capacity);

// TODO: resolve LIS from TAIL

t_tail	*tail_get(t_stack *stack, size_t start_index)
{
	t_tail	*tail;
	size_t	i;
	size_t	index;

	tail = tail_new(start_index, stack->count);
	if (!tail)
		return (NULL);
	i = 0;
	while (i < stack->count)
	{
		index = (start_index + i) % stack->count;
		tail_update(tail, stack->values[index], (int)index);
		i++;
	}
	return (tail);
}

static t_tail	*tail_new(size_t start_index, size_t capacity)
{
	t_tail	*tail;

	tail = malloc(sizeof *tail);
	if (!tail)
		return (NULL);
	tail->start_index = start_index;
	tail->array = NULL;
	tail->pos = NULL;
	tail->prev = NULL;
	tail->array = malloc(capacity * sizeof *tail->array);
	tail->pos = malloc(capacity * sizeof *tail->pos);
	tail->prev = malloc(capacity * sizeof *tail->prev);
	if (!tail->array || !tail->pos || !tail->prev)
	{
		tail_free(&tail);
		return (NULL);
	}
	ft_memset(tail->pos, -1, capacity * sizeof *tail->pos);
	ft_memset(tail->prev, -1, capacity * sizeof *tail->prev);
	tail->max_len = 0;
	return (tail);
}

static void	tail_update(t_tail *tail, int value, int index)
{
	size_t	lower_index;
	int 	left;
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
		tail->prev[index] = tail->pos[lower_index - 1];
	else
		tail->prev[index] = -1;
}

void	tail_free(t_tail **tail)
{
	if (!tail || !*tail)
		return ;
	if ((*tail)->array)
		free((*tail)->array);
	if ((*tail)->pos)
		free((*tail)->pos);
	if ((*tail)->prev)
		free((*tail)->prev);
	free(*tail);
	*tail = NULL;
}

// static void	tail_print(t_tail *tail, size_t capacity)
// {
// 	size_t	i;

// 	fprintf(stderr, "\n-----TAIL-----\n");
// 	fprintf(stderr, "start_index = %zu\n", tail->start_index);
// 	fprintf(stderr, "max_len     = %zu\n", tail->max_len);
// 	fprintf(stderr, "array       = [");
// 	i = 0;
// 	while (i < tail->max_len)
// 	{
// 		fprintf(stderr, "%i ", tail->array[i]);
// 		i++;
// 	}
// 	fprintf(stderr, "]\n");
// 	fprintf(stderr, "pos         = [");
// 	i = 0;
// 	while (i < tail->max_len)
// 	{
// 		fprintf(stderr, "%i ", tail->pos[i]);
// 		i++;
// 	}
// 	fprintf(stderr, "]\n");
// 	fprintf(stderr, "prev        = [");
// 	i = 0;
// 	while (i < capacity)
// 	{
// 		fprintf(stderr, "%i ", tail->prev[i]);
// 		i++;
// 	}
// 	fprintf(stderr, "]\n");
// 	fprintf(stderr, "--------------\n");
// }
