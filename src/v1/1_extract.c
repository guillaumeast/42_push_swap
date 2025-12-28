#include "push_swap.h"
#include "libft.h"

static void	extract_from_a_to_b(t_stack *a, t_stack *b);
static void	extract_chunk(t_stack *a, t_stack *b, int min, int max);
static int	get_cheapest_index(t_stack *a, int min, int max);

bool	step_1(t_stack *a, t_stack *b)
{
	extract_from_a_to_b(a, b);
	return (true);
}

static void	extract_from_a_to_b(t_stack *a, t_stack *b)
{
	int		k;
	int		min;
	int		max;

	k = 3 * square_root_rounded((int)a->cap);
	min = 0;
	max = k;
	while (min < (int)a->cap)
	{
		extract_chunk(a, b, min, max);
		min = max;
		max = min + k;
	}
}

static void	extract_chunk(t_stack *a, t_stack *b, int min, int max)
{
	int	i;
	int	median;
	int	rr_needed;

	median = min + ((max - min) / 2);
	while (true)
	{
		i = get_cheapest_index(a, min, max);
		if (i == -1)
			break ;
		if (i <= (int)a->count - 1 - i)
		{
			while (i-- > 0)
				rotate(a, b, A);
		}
		else
		{
			rr_needed = (int)a->count - i;
			while (rr_needed-- > 0)
				rotate_reverse(a, b, A);
		}
		push(a, b, B);
		if (b->values[0] < median)
			rotate(a, b, B);
	}
}

static int	get_cheapest_index(t_stack *a, int min, int max)
{
	int	first_from_top;
	int	first_from_bottom;
	int	cost_from_top;
	int	cost_from_bottom;
	int	i;

	i = 0;
	while (i < (int)a->count && (a->values[i] < min || a->values[i] >= max))
		i++;
	if (i >= (int)a->count)
		return (-1);
	first_from_top = i;
	i = (int)a->count - 1;
	while (i >= 0 && (a->values[i] < min || a->values[i] >= max))
		i--;
	first_from_bottom = i;
	cost_from_top = first_from_top;
	cost_from_bottom = (int)a->count - first_from_bottom;
	if (cost_from_top <= cost_from_bottom)
		return (first_from_top);
	return (first_from_bottom);
}
