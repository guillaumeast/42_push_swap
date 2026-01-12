#include "stack.h"

static void	rotate(t_stack *stack, bool reverse);
static void	swap(t_stack *stack);

t_move	stack_rotate(t_stack *a, t_stack *b, t_target target, bool reverse)
{
	if (target == A && a->len > 1 && reverse)
		return (rotate(a, reverse), RRA);
	else if (target == A && a->len > 1 && !reverse)
		return (rotate(a, reverse), RA);
	else if (target == B && b->len > 1 && reverse)
		return (rotate(b, reverse), RRB);
	else if (target == B && b->len > 1 && !reverse)
		return (rotate(b, reverse), RB);
	else if (target == BOTH && (a->len > 1 || b->len > 1) && reverse)
		return (rotate(a, reverse), rotate(b, reverse), RRR);
	else if (target == BOTH  && (a->len > 1 || b->len > 1)&& !reverse)
		return (rotate(a, reverse), rotate(b, reverse), RR);
	return (NO_OP);
}

static void	rotate(t_stack *stack, bool reverse)
{
	if (stack->len < 2)
		return ;
	if (reverse)
	{
		stack->offset = (stack->offset - 1) % stack->cap;
		while (stack->values[stack->offset] == -1)
			stack->offset = (stack->offset - 1) % stack->cap;
	}
	else
	{
		stack->offset = (stack->offset + 1) % stack->cap;
		while (stack->values[stack->offset] == -1)
			stack->offset = (stack->offset + 1) % stack->cap;
	}
}

t_move	stack_swap(t_stack *a, t_stack *b, t_target target)
{
	if (target == A && a->len > 1)
		return (swap(a), SA);
	else if (target == B && b->len > 1)
		return (swap(b), SB);
	else if (target == BOTH && (a->len > 1 || b->len > 1))
		return (swap(a), swap(b), SS);
	return (NO_OP);
}

static void	swap(t_stack *stack)
{
	int		tmp;
	size_t	i;

	if (stack->len < 2)
		return ;

	i = stack->offset + 1;
	while (stack->values[i] == -1)
		i = (i + 1) % stack->cap;
	tmp = stack->values[stack->offset];
	stack->values[stack->offset] = stack->values[i];
	stack->values[i] = tmp;
}

t_move	stack_push(t_stack *from, t_stack *to, t_target target)
{
	int		deleted;
	int		tmp_for_swap;
	size_t	i;

	if (target == BOTH || from->len == 0)
		return (NO_OP);
	i = (to->offset = (to->offset - 1) % to->cap);
	deleted = to->values[i];
	to->values[i] = from->values[from->offset];
	from->values[from->offset] = -1;
	from->len--;
	to->len++;
	if (from->len > 0)
		while (from->values[from->offset] == -1)
			from->offset = (from->offset + 1) % from->cap;
	while (deleted != -1)
	{
		i = (i - 1) % to->cap;
		tmp_for_swap = to->values[i];
		to->values[i] = deleted;
		deleted = tmp_for_swap;
	}
	if (target == A)
		return (PA);
	return (PB);
}
