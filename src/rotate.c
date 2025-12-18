#include "push_swap.h"
#include <unistd.h>

static void	rotate_stack(t_stack *stack);
static void	rotate_reverse_stack(t_stack *stack);

void	rotate(t_stack *a, t_stack *b, t_stack_choice choice)
{
	if (choice == A && a->count > 1)
	{
		write(1, "ra\n", 3);
		rotate_stack(a);
	}
	else if (choice == B && b->count > 1)
	{
		write(1, "rb\n", 3);
		rotate_stack(b);
	}
	else if (choice == BOTH && (a->count > 1 || b->count > 1))
	{
		write(1, "rr\n", 3);
		rotate_stack(a);
		rotate_stack(b);
	}
}

static void	rotate_stack(t_stack *stack)
{
	int		tmp;
	size_t	i;

	tmp = stack->values[0];
	i = 0;
	while (i < stack->count - 1)
	{
		stack->values[i] = stack->values[i + 1];
		i++;
	}
	stack->values[i] = tmp;
}

void	rotate_reverse(t_stack *a, t_stack *b, t_stack_choice choice)
{
	if (choice == A && a->count > 1)
	{
		write(1, "rra\n", 3);
		rotate_reverse_stack(a);
	}
	else if (choice == B && b->count > 1)
	{
		write(1, "rrb\n", 3);
		rotate_reverse_stack(b);
	}
	else if (choice == BOTH && (a->count > 1 || b->count > 1))
	{
		write(1, "rrr\n", 3);
		rotate_reverse_stack(a);
		rotate_reverse_stack(b);
	}
}

static void	rotate_reverse_stack(t_stack *stack)
{
	int		tmp;
	size_t	i;

	tmp = stack->values[stack->count - 1];
	i = stack->count - 1;
	while (i > 0)
	{
		stack->values[i] = stack->values[i - 1];
		i--;
	}
	stack->values[0] = tmp;
}
