#include "stack.h"
#include <stdlib.h>

static void	rotate(t_stack *stack, bool reverse);
static void	swap(t_stack *stack);
bool	push_from(t_stack *stack, int *ret);
bool	push_to(t_stack *stack, int value);

t_move	stack_rotate(t_stack *a, t_stack *b, t_target target, bool reverse)
{
	if (target == A && a->size > 1 && reverse)
		return (rotate(a, reverse), RRA);
	else if (target == A && a->size > 1 && !reverse)
		return (rotate(a, reverse), RA);
	else if (target == B && b->size > 1 && reverse)
		return (rotate(b, reverse), RRB);
	else if (target == B && b->size > 1 && !reverse)
		return (rotate(b, reverse), RB);
	else if (target == BOTH && (a->size > 1 || b->size > 1) && reverse)
		return (rotate(a, reverse), rotate(b, reverse), RRR);
	else if (target == BOTH  && (a->size > 1 || b->size > 1)&& !reverse)
		return (rotate(a, reverse), rotate(b, reverse), RR);
	return (NO_OP);
}

static void	rotate(t_stack *stack, bool reverse)
{
	if (stack->size < 2)
		return ;
	if (reverse)
		stack->offset = (stack->offset - 1) % stack->size;
	else
		stack->offset = (stack->offset + 1) % stack->size;
}

t_move	stack_swap(t_stack *a, t_stack *b, t_target target)
{
	if (target == A && a->size > 1)
		return (swap(a), SA);
	else if (target == B && b->size > 1)
		return (swap(b), SB);
	else if (target == BOTH && (a->size > 1 || b->size > 1))
		return (swap(a), swap(b), SS);
	return (NO_OP);
}

static void	swap(t_stack *stack)
{
	size_t	next_index;
	int		tmp;

	if (stack->size < 2)
		return ;
	next_index = (stack->offset + 1) % stack->size;
	tmp = stack->data[stack->offset];
	stack->data[stack->offset] = stack->data[next_index];
	stack->data[next_index] = tmp;
}

# include <stdio.h>
t_move	stack_push(t_stack *from, t_stack *to, t_target target)
{
	int	moved_value;

	if (from->size == 0)
		return (NO_OP);
	if (!push_from(from, &moved_value))
		return (ERROR);
	printf("-----> BEFORE push_to()\n");
	stack_print(from, to);
	if (!push_to(to, moved_value))
		return (ERROR);
	printf("-----> AFTER push_to()\n");
	stack_print(from, to);
	printf("\n-----\n");
	if (target == A)
		return (PA);
	return (PB);
}

bool	push_from(t_stack *stack, int *ret)
{
	int		*new_data;
	size_t	new_size;
	int		*src_ptr;
	size_t	bytes_before;
	size_t	bytes_after;

	*ret = stack->data[stack->offset];
	new_size = stack->size - 1;
	new_data = malloc(new_size * sizeof *new_data);
	if (!new_data)
		return (false);
	bytes_before = stack->offset * sizeof(int);
	ft_memcpy(new_data, stack->data, bytes_before);
	src_ptr = stack->data + ((stack->offset + 1) % stack->size);
	bytes_after = (stack->size - stack->offset - 1) * sizeof(int);
	ft_memcpy(new_data + stack->offset, src_ptr, bytes_after);
	free(stack->data);
	stack->data = new_data;
	stack->size = new_size;
	return (true);
}

bool	push_to(t_stack *stack, int value)
{
	int		*new_data;
	size_t	new_size;
	int		*dst_ptr;
	int		*src_ptr;
	size_t	bytes_after;

	printf("Pushing to...\n");
	new_size = stack->size + 1;
	new_data = malloc(new_size * sizeof *new_data);
	if (!new_data)
		return (false);
	if (new_size > 1)
	{
		printf("Copying %zu bytes from index 0...\n", stack->offset);
		ft_memcpy(new_data, stack->data, stack->offset * sizeof(int));
		dst_ptr = new_data + ((stack->offset + 1) % new_size);
		src_ptr = stack->data + stack->offset;
		bytes_after = (stack->size - stack->offset) * sizeof(int);
		printf("Copying %zu bytes from index [dst = %zu] to index [src = %zu]...\n", bytes_after, dst_ptr - new_data, stack->offset);
		ft_memcpy(dst_ptr, src_ptr, bytes_after);
		printf("Modifying index %zu of new_data...\n", stack->offset);
	}
	new_data[stack->offset] = value;
	if (stack->data)
		free(stack->data);
	stack->data = new_data;
	stack->size++;
	printf("done\n");
	return (true);
}
