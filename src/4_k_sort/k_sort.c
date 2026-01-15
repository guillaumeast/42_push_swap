#include "libft.h"
#include "stack.h"

# include <stdio.h>
bool	k_sort(t_stack *a, t_stack *b, t_buff *move_list)
{
	char	move;

	while (a->len > 2)
	{
		move = (char)stack_push(a, b, B);
		if (move == ERROR || !buff_append(move_list, &move, 1))
			return (false);
	}
	return (true);
}

// void	k_sort(t_stack *a, t_stack *b)
// {
// 	size_t	window_max;
// 	size_t	i;

// 	window_max = a->len / 6;
// 	i = 0;
// 	while (a->len > 3)
// 	{

// 	}
// }

// static size_t	static_window_size(t_stack *a, t_stack *b)
// {
// 	size_t	i;
// 	int		window_max;
// 	size_t	move_count;

// 	window_max = (int)(a->len / 6);
// 	move_count = 0;
// 	i = 0;
// 	while (a->len > 2)
// 	{
// 		if (a->values[i] < window_max)

// 	}
// }
