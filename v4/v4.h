#ifndef V4_H
# define V4_H

#include "push_swap.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct s_tail
{
	size_t	start_index;
	int		*array;
	size_t	max_len;
	int		*pos;
	int		*prev;
}	t_tail;

typedef struct s_lis
{
	size_t	start_index;
	bool	*keep;
	size_t	keep_count;
	bool	*swap;
	size_t	swap_count;
	size_t	final_len;
}	t_lis;

t_tail	*tail_get(t_stack *stack, size_t start_index);
void	tail_free(t_tail **tail);

t_lis	*lis_get_best(t_stack *stack);
void	lis_free(t_lis **lis);

#endif
