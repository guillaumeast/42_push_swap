#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	rr(t_stack *a, t_stack *b, size_t count, t_buff *list)
{
	stack_rotate(a, count);
	stack_rotate(b, count);
	return (move_add(RR, count, list));
}

bool	ra(t_stack *a, size_t count, t_buff *list)
{
	stack_rotate(a, count);
	return (move_add(RA, count, list));
}

bool	rb(t_stack *b, size_t count, t_buff *list)
{
	stack_rotate(b, count);
	return (move_add(RB, count, list));
}
