#include "stack_ops.h"
#include "moves.h"

bool	ss(t_stack *a, t_stack *b, t_buff *list)
{
	stack_swap(a);
	stack_swap(b);
	return (move_add(SS, 1, list));
}

bool	sa(t_stack *a, t_buff *list)
{
	stack_swap(a);
	return (move_add(SA, 1, list));
}

bool	sb(t_stack *b, t_buff *list)
{
	stack_swap(b);
	return (move_add(SB, 1, list));
}
