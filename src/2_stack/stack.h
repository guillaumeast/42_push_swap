#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>


typedef struct s_stack
{
	uint	*data;
	size_t	offset;
	size_t	len;
	size_t	cap;
}	t_stack;

typedef enum e_target
{
	A,
	B,
	BOTH
}	t_target;

typedef enum e_move
{
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SA,
	SB,
	SS,
	PA,
	PB,
	NO_OP,
	ERROR
}	t_move;

/* TODO: tmp debug */
# include "libft.h"
void	stack_print(t_stack *a, t_stack *b);
void	moves_print(t_buff *move_list);

/*---------- stack.c ----------*/

bool	stack_init(t_stack *a, t_stack *b, uint *values, size_t count);
bool	stack_dup(t_stack *dst, t_stack *src);
uint	stack_get_value(t_stack *stack, size_t index);
size_t	stack_get_target_index(t_stack *s, uint value);
bool	stack_is_sorted(t_stack *stack);

/*---------- moves.c ----------*/

t_move	stack_rotate(t_stack *a, t_stack *b, t_target target, bool reverse);
t_move	stack_swap(t_stack *a, t_stack *b, t_target target);
t_move	stack_push(t_stack *from, t_stack *to, t_target target);

#endif
