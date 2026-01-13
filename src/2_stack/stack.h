#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>

# define EMPTY_CELL -1

typedef struct s_stack
{
	int		*values;
	size_t	offset;
	size_t	cap;
	size_t	len;
}	t_stack;

typedef struct s_stack_index
{
	int	real;
	int	virtual;
}	t_stack_index;

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

/* TODO: tmp debug */
void	stack_print(t_stack *a, t_stack *b);

/*---------- stack.c ----------*/

bool	stack_init(t_stack *stack, int *values, size_t count);
bool	stack_dup(t_stack *dst, t_stack *src);
int		stack_get_value(t_stack *stack, size_t index);
int		stack_get_target_index(t_stack *s, int value);
bool	stack_is_sorted(t_stack *stack);

/*---------- moves.c ----------*/

t_move	stack_rotate(t_stack *a, t_stack *b, t_target target, bool reverse);
t_move	stack_swap(t_stack *a, t_stack *b, t_target target);
t_move	stack_push(t_stack *from, t_stack *to, t_target target);

#endif
