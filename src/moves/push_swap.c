#include "push_swap.h"
#include <unistd.h>

static void	push_stack(t_stack *from, t_stack *to);
static void	swap_stack(t_stack *stack);

void	push(t_stack *a, t_stack *b, t_stack_choice choice)
{
	if (choice == A && b->count > 0)
	{
		write(1, "pa\n", 3);
		push_stack(b, a);
		g_move_count++;
	}
	else if (choice == B && a->count > 0)
	{
		write(1, "pb\n", 3);
		push_stack(a, b);
		g_move_count++;
	}
	// debug_print(a, b);
}

static void	push_stack(t_stack *from, t_stack *to)
{
	size_t	i;

	i = to->count + 1;
	while (--i > 0)
		to->values[i] = to->values[i - 1];
	to->values[0] = from->values[0];
	to->count++;
	i = 1;
	while (i < from->count)
	{
		from->values[i - 1] = from->values[i];
		i++;
	}
	from->count--;
}

void	swap(t_stack *a, t_stack *b, t_stack_choice choice)
{
	if (choice == A && a->count > 1)
	{
		write(1, "sa\n", 3);
		swap_stack(a);
		g_move_count++;
	}
	else if (choice == B && b->count > 1)
	{
		write(1, "sb\n", 3);
		swap_stack(b);
		g_move_count++;
	}
	else if (choice == BOTH && (a->count > 1 || b->count > 1))
	{
		write(1, "ss\n", 3);
		swap_stack(a);
		swap_stack(b);
		g_move_count++;
	}
	// debug_print(a, b);
}

static void	swap_stack(t_stack *stack)
{
	int	tmp;

	tmp = stack->values[0];
	stack->values[0] = stack->values[1];
	stack->values[1] = tmp;
}
