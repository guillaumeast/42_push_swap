#include "stack_ops.h"
#include "moves.h"

bool	pa(t_stack *a, t_stack *b, size_t count, t_buff *list)
{
	stack_push(b, a, count);
	return (move_add(PA, count, list));
}

bool	pb(t_stack *a, t_stack *b, size_t count, t_buff *list)
{
	stack_push(a, b, count);
	return (move_add(PB, count, list));
}
