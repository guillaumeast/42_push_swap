#include "push_swap.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>

/*
* TODO
* 1. Remplacer mon charabia par un vrai TAIL pour trouver LIS (sans swap mais avec cycle % a->count !)
* 2. Reconstruire quels éléments garder
* 3. Exécuter la LIS trouvée (en optimisant localement avec swaps si A[i] > A[i + 1] && A[i] < A[i + 2])
*/

typedef struct s_lis
{
	size_t	index;		// starting index
	size_t	rotations;	// real alignement cost => min(index, count - index)
	size_t	len;		// len, including swaps
	size_t	swaps;		// number of independant local swaps (swap only if A[i] > A[i + 1] && A[i] < A[i + 2] (then LOCK i, i + 1 and i + 2)
	int		*values;		// virtual values of A (rotated and swapped)
	bool	*locked;	// array (size = a->count) which stores locked state of each A index (true = already swapped => no more swap allowed)
	int		score;		// = len - (rotations + swaps)
}	t_lis;

static t_lis	*lis_new(t_stack *a, size_t index);
static void		lis_compute(t_stack *a, t_lis *lis);
static void		lis_swap(t_stack *a, t_lis *lis, size_t index);
static void		lis_execute(t_stack *a, t_stack *b, t_lis *lis);
static void		lis_free_all(t_lis **lis_list, size_t count);

bool	step_1(t_stack *a, t_stack *b)
{
	t_lis	**lis_list;
	int		best_score;
	t_lis	*best_lis;
	size_t	i;

	lis_list = malloc(a->count * sizeof *lis_list);
	if (!lis_list)
		return (false);
	i = 0;
	best_score = INT_MIN;
	best_lis = NULL;
	while (i < a->count)
	{
		lis_list[i] = lis_new(a, i);
		if (!lis_list[i])
			break ;
		lis_compute(a, lis_list[i]);
		if (!best_lis || lis_list[i]->score > best_score)
		{
			best_score = lis_list[i]->score;
			best_lis = lis_list[i];
		}
		i++;
	}
	if (best_lis)
		lis_execute(a, b, best_lis);
	lis_free_all(lis_list, a->count);
	return (true);
}

static t_lis	*lis_new(t_stack *a, size_t index)
{
	t_lis	*lis;

	lis = malloc(sizeof *lis);
	if (!lis)
		return (NULL);
	lis->values = malloc(a->count * sizeof *lis->values);
	if (!lis->values)
		return (free(lis), NULL);
	ft_memcpy(lis->values, a->values, a->count * sizeof *a->values);
	lis->locked = malloc(a->count * sizeof *lis->locked);
	if (!lis->locked)
		return (free(lis), free(lis->values), NULL);
	ft_bzero(lis->locked, a->count * sizeof *lis->locked);
	lis->index = index;
	if (index < a->count / 2)
		lis->rotations = index;
	else
	 	lis->rotations = a->count - index;
	lis->len = 0;
	lis->swaps = 0;
	lis->score = INT_MIN;
	return (lis);
}

static void	lis_compute(t_stack *a, t_lis *lis)
{
	size_t	i;
	size_t	index;

	i = 0;
	while (i < a->count)
	{
		index = (i + lis->index) % a->count;
		lis_swap(a, lis, index);
		if (i > 0 && lis->values[index] > lis->values[index - 1])
			lis->len++;
		i++;
	}
	lis->score = (int)(lis->len - (lis->rotations + lis->swaps));
}

static void	lis_swap(t_stack *a, t_lis *lis, size_t index)
{
	int		tmp;

	if (index + 1 >= a->count || lis->locked[index] || lis->locked[index + 1]
		|| (lis->values[index] < lis->values[index + 1])
		|| (index + 2 < a->count && lis->locked[index + 2])
		|| (index + 2 < a->count && lis->values[index] > lis->values[index + 2])
	)
		return ;
	tmp = lis->values[index];
	lis->values[index] = lis->values[index + 1];
	lis->values[index + 1] = tmp;
	lis->locked[index] = true;
	lis->locked[index + 1] = true;
	if (index + 2 < a->count)
		lis->locked[index + 2] = true;
	lis->swaps++;
}

static void	lis_execute(t_stack *a, t_stack *b, t_lis *lis)
{
	size_t	i;
	int		last_locked_i;

	last_locked_i = -1;
	i = lis->index;
	if (lis->index < a->count / 2)
	{
		while (i > 0)
		{
			rotate(a, b, A);
			i--;
		}
	}
	else
	{
		while (i > 0)
		{
			rotate_reverse(a, b, A);
			i--;
		}
	}
	while (i < a->count)
	{
		if (i + 2 < a->count && i + 2 > (size_t)last_locked_i)
		{
			if (a->values[i] > a->values[i + 1] && a->values[i] < a->values[i + 2])
			{
				swap(a, b, A);
				last_locked_i = (int)i + 2;
			}
		}
		else if (i + 1 < a->count && i + 1 > (size_t)last_locked_i && a->values[i] > a->values[i + 1])
		{
			swap(a, b, A);
			last_locked_i = (int)i + 1;
		}
		if (i > 0 && a->values[i] > a->values[i - 1])
			rotate(a, b, A);
		else
			push(a, b, B);
		i++;
	}
}

static void	lis_free_all(t_lis **lis_list, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(lis_list[i]->values);
		free(lis_list[i]->locked);
		free(lis_list[i]);
		i++;
	}
	free(lis_list);
	lis_list = NULL;
}
