#include "stack_ops.h"
#include "moves.h"
#include "moves_priv.h"

bool	rrr(t_stack *a, t_stack *b, size_t count, t_buff *list)
{
	stack_reverse_rotate(a, count);
	stack_reverse_rotate(b, count);
	return (move_add(RRR, count, list));
}

bool	rra(t_stack *a, size_t count, t_buff *list)
{
	stack_reverse_rotate(a, count);
	return (move_add(RRA, count, list));
}

bool	rrb(t_stack *b, size_t count, t_buff *list)
{
	stack_reverse_rotate(b, count);
	return (move_add(RRB, count, list));
}
