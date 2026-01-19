#ifndef MOVES_H
# define MOVES_H

# include "libft.h"
# include "stack.h"

/* --- rotate.c --- */

bool	rr(t_stack *a, t_stack *b, size_t count, t_buff *list);
bool	ra(t_stack *a, size_t count, t_buff *list);
bool	rb(t_stack *b, size_t count, t_buff *list);

/* --- rotate_reverse.c --- */

bool	rrr(t_stack *a, t_stack *b, size_t count, t_buff *list);
bool	rra(t_stack *a, size_t count, t_buff *list);
bool	rrb(t_stack *b, size_t count, t_buff *list);

/* --- swap.c --- */

bool	ss(t_stack *a, t_stack *b, t_buff *list);
bool	sa(t_stack *a, t_buff *list);
bool	sb(t_stack *b, t_buff *list);

/* --- push.c --- */

bool	pa(t_stack *a, t_stack *b, size_t count, t_buff *list);
bool	pb(t_stack *a, t_stack *b, size_t count, t_buff *list);

/* --- add.c --- */

bool	move_add(char move, size_t count, t_buff *list);

/* --- print.c --- */

void	moves_print(t_buff *list);

#endif
