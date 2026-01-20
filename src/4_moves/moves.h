#ifndef MOVES_H
# define MOVES_H

# include "libft.h"
# include "state.h"

/* --- rotate.c --- */

bool	rr(t_state *state, size_t count);
bool	ra(t_state *state, size_t count);
bool	rb(t_state *state, size_t count);

/* --- rotate_reverse.c --- */

bool	rrr(t_state *state, size_t count);
bool	rra(t_state *state, size_t count);
bool	rrb(t_state *state, size_t count);

/* --- swap.c --- */

bool	ss(t_state *state);
bool	sa(t_state *state);
bool	sb(t_state *state);

/* --- push.c --- */

bool	pa(t_state *state, size_t count);
bool	pb(t_state *state, size_t count);

/* --- print.c --- */

void	moves_print(t_buff *list);

#endif
