#include "stack.h"
#include <stdlib.h>

static void	rotate(t_stack *stack, bool reverse);
static void	swap(t_stack *stack);
bool		push_from(t_stack *stack, uint *ret);
bool		push_to(t_stack *stack, uint value);

// t_move	move_do(t_stack *a, t_stack *b, t_move move);
// bool	move_save(t_buff *list, t_move move);

// bool	move_do_and_save(t_stack *a, t_stack *b, t_move move, size_t count, t_buff *list)
// {
// 	while (count > 0)
// 	{
// 		move = move_do(a, b, move);
// 		move_save(list, move);
// 		count--;
// 	}
// 	return (true);
// }

// t_move	move_do(t_stack *a, t_stack *b, t_move move)
// {
// 	if (move == RR)
// 		return (stack_rotate(a, b, BOTH, false));
// 	else if (move == RA)
// 		return (stack_rotate(a, b, A, false));
// 	else if (move == RB)
// 		return (stack_rotate(a, b, B, false));
// 	else if (move == RRR)
// 		return (stack_rotate(a, b, BOTH, true));
// 	else if (move == RRA)
// 		return (stack_rotate(a, b, A, true));
// 	else if (move == RRB)
// 		return (stack_rotate(a, b, B, true));
// 	else if (move == SS)
// 		return (stack_swap(a, b, BOTH));
// 	else if (move == SA)
// 		return (stack_swap(a, b, A));
// 	else if (move == SB)
// 		return (stack_swap(a, b, B));
// 	else if (move == PA)
// 		return (stack_push(b, a, A));
// 	else if (move == PB)
// 		return (stack_push(a, b, B));
// 	else
// 		return (NO_OP);
// }

// bool	move_save(t_buff *list, t_move move)
// {
// 	char	enum_as_char;

// 	if (move == NO_OP)
// 		return (true);
// 	enum_as_char = (char)move;
// 	return (!buff_append(list, &enum_as_char, 1));
// }

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
		stack->offset = modulo((long)stack->offset - 1, stack->len);
	else
		stack->offset = (stack->offset + 1) % stack->len;
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
	size_t	next_index;
	uint	tmp;

	if (stack->len < 2)
		return ;
	next_index = (stack->offset + 1) % stack->len;
	tmp = stack->data[stack->offset];
	stack->data[stack->offset] = stack->data[next_index];
	stack->data[next_index] = tmp;
}

t_move	stack_push(t_stack *from, t_stack *to, t_target target)
{
	uint	*dst_ptr;
	uint	*src_ptr;
	size_t	len_to_move;

	if (from->len == 0)
		return (NO_OP);
	src_ptr = to->data + to->offset;
	dst_ptr = src_ptr + 1;
	len_to_move = (to->len - to->offset) * sizeof * (to->data);
	ft_memmove(dst_ptr, src_ptr, len_to_move);
	to->data[to->offset] = from->data[from->offset];
	to->len++;
	if (from->offset != from->len - 1)
	{
		dst_ptr = from->data + from->offset;
		src_ptr = dst_ptr + 1;
		len_to_move = (from->len - from->offset - 1) * sizeof * (from->data);
		ft_memmove(dst_ptr, src_ptr, len_to_move);
	}
	else
		from->offset = 0;
	from->len--;
	if (target == A)
		return (PA);
	return (PB);
}
