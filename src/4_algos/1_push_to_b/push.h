#ifndef PUSH_H
# define PUSH_H

# include "libft.h"
# include "stack.h"

typedef struct t_push_opti
{
	bool	swap;
	bool	median;
}	t_push_opti;

bool	push_to_b(t_stack *a, t_stack *b, t_push_opti *opti, t_buff *list);

#endif
