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
}	t_lis;

bool	lis_compute_both(const t_stack *stack, t_lis *lis, t_lis *lis_swap);
void	lis_free(t_lis *lis);

#endif
