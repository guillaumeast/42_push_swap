#ifndef STATE_H
# define STATE_H

# include "libft.h"
# include "stack.h"

typedef struct s_state
{
	t_stack a;
	t_stack	b;
	t_buff	moves;
}	t_state;

bool	state_init(t_state *dst, uint *values, size_t values_size);
bool	state_dup(t_state *dst, const t_state *src);
void	state_free(t_state *state);

#endif
