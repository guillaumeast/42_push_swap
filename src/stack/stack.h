#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_stack
{
	int		*values;
	size_t	offset;
	size_t	cap;
	size_t	len;
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
	NO_OP
}	t_move;

/*---------- stack.c ----------*/

t_stack	stack_new(int *values, size_t offset, size_t count, size_t len);
bool	stack_dup(t_stack *dst, t_stack *src);
int		stack_get_value(t_stack *stack, size_t index);

/*---------- moves.c ----------*/

t_move	stack_rotate(t_stack *a, t_stack *b, t_target target, bool reverse);
t_move	stack_swap(t_stack *a, t_stack *b, t_target target);
t_move	stack_push(t_stack *a, t_stack *b, t_target target);

#endif
