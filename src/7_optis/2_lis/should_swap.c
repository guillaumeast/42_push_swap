#include "stack.h"
# include "debug.h"	// TMP: remove before submit

static void	print_future(size_t depth, long value);	// TMP: remove before submit

uint	future(t_stack *stack, size_t index, size_t depth)
{
	uint	current;
	uint	second;
	uint	third;


	print_future(depth, -1);
	current = stack_get_value(stack, index);
	if (index > stack->len)
	{
		print_future(depth, (long)current);
		return (current);
	}
	second = stack_get_value(stack, index + 1);
	if (current < second)
	{
		print_future(depth, (long)current);
		return (current);
	}
	third = future(stack, index + 2, depth + 1);
	if (current > third)
	{
		print_future(depth, (long)current);
		return (current);
	}
	print_future(depth, (long)second);
	return (second);
}

bool	should_swap(t_stack *stack, size_t index)
{
	uint	current;
	uint	second;
	uint	third;

	if (index > stack->len)
		return (false);
	current = stack_get_value(stack, index);
	second = stack_get_value(stack, index + 1);
	third = stack_get_value(stack, index + 2);
	if (current < second)
		return (false);
	if (current < third)
		return (true);
	return (current < future(stack, index + 2, 1));
}

// TMP: remove before submit
static void	print_future(size_t depth, long value)
{
	size_t	i;

	i = 0;
	while (i++ < depth)
		fprintf(stderr, "=");
	if (value > 0)
		fprintf(stderr, "> future [%zu] = %ld", depth, value);
	else
		fprintf(stderr, "> future [%zu]...", depth);
}
