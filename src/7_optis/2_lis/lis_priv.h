#ifndef LIS_PRIV_H
# define LIS_PRIV_H

# include "stack.h"
# include <stddef.h>

typedef struct s_tail
{
	size_t	start_index;
	uint	*array;
	size_t	max_len;
	size_t	*pos;
	long	*prev;
}	t_tail;

bool	tail_compute(t_tail *tail, t_stack *stack, size_t start_index);
void	tail_free(t_tail *tail);

#endif
