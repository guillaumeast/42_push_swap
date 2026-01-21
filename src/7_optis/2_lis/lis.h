#ifndef LIS_H
# define LIS_H

# include "stack.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_lis
{
	size_t	start_index;
	bool	*keep;
	size_t	keep_count;
	bool	*swap;
	size_t	swap_count;
	size_t	final_len;
}	t_lis;

// WARNING: only works if stack->offset == 0 !!!
bool	lis_compute_best(t_stack *stack, t_lis *lis, bool enable_swap);
void	lis_free(t_lis *lis);

#endif
