#include "libft.h"
#include "lis_priv.h"
#include "stack_ops.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

// TODO: compute swaps backward !!

static bool	set_stack_1(t_swapped_stack *dst, t_stack *src);
static bool	set_stack_2(t_stack *stk, t_swapped_stack *v1, t_swapped_stack *v2);
static void compute_swaps(t_swapped_stack *stack, long start, long end);
static void	free_all(t_lis *lis, t_swapped_stack *stack_1, t_swapped_stack *stack_2);

bool	lis_compute_both(t_stack *stack, t_lis *lis, t_lis *lis_swap)
{
	t_swapped_stack	stack_1;
	t_swapped_stack	stack_2;

	fprintf(stderr, "[🔦 DEBUG] lis_compute_both()...\n");
	if (!lis_best(stack, NULL, lis))
		return (false);
	if (!set_stack_1(&stack_1, stack))
		return (free_all(lis, NULL, NULL), false);
	compute_swaps(&stack_1, (long)stack->len - 2, (long)stack->len - 1);
	fprintf(stderr, "stack_1->swaps = ");
	print_bool_array(stack_1.swaps, stack_1.stack.len);
	stack_print(stack, &stack_1.stack);
	if (stack_1.first_swapped)
	{
		fprintf(stderr, "Setting stack_2...\n");
		if (!set_stack_2(stack, &stack_1, &stack_2))
			return (free_all(lis, &stack_1, NULL), false);
		fprintf(stderr, "Computing swaps...\n");
		compute_swaps(&stack_2, (long)stack->len - 2, (long)stack->len -1);
		fprintf(stderr, "stack_2->swaps = ");
		print_bool_array(stack_2.swaps, stack->len);
		stack_print(stack, &stack_1.stack);
		if (!lis_best_between(&stack_1, &stack_2, lis_swap))
			return (free_all(lis, &stack_1, &stack_2), false);
		fprintf(stderr, "\n[🔦 DEBUG] RESULTS:\n");
		lis_print(lis, stack->len);
		lis_print(lis_swap, stack->len);
		return (free_all(NULL, &stack_1, &stack_2), true);
	}
	else if (!lis_best(&stack_1.stack, stack_1.swaps, lis_swap))
		return (free_all(lis, &stack_1, NULL), false);
	fprintf(stderr, "\n[🔦 DEBUG] RESULTS:\n");
	lis_print(lis, stack->len);
	lis_print(lis_swap, stack->len);
	return (free_all(NULL, &stack_1, NULL), true);
}

static bool	set_stack_1(t_swapped_stack *dst, t_stack *src)
{
	if (!stack_dup(&dst->stack, src))
		return (false);
	dst->swaps = malloc(src->len * sizeof * dst->swaps);
	if (!dst->swaps)
		return (free(dst->stack.data), false);
	ft_memset(dst->swaps, false, src->len * sizeof * dst->swaps);
	dst->first_swapped = false;
	return (true);
}

static bool	set_stack_2(t_stack *stk, t_swapped_stack *v1, t_swapped_stack *v2)
{
	if (!v2)
		return (true);

	if (!stack_dup(&v2->stack, &v1->stack))
		return (false);
	v2->swaps = malloc(v2->stack.len * sizeof * v2->swaps);
	if (!v2->swaps)
		return (free(v2->stack.data), false);
	ft_memcpy(v2->swaps, v1->swaps, v2->stack.len * sizeof * v2->swaps);
	v2->first_swapped = false;
	v2->swaps[stack_get_value(stk, 0)] = false;
	v2->swaps[stack_get_value(stk, 1)] = false;
	ft_memcpy(v2->stack.data, stk->data, 3 * sizeof * v2->stack.data);
	return (true);
}

// NOTE: Computes backward to allow as much swaps as possible
// A B C D => A must be < C to swap so best possibilities if swap(C, D) is possible because it means that D < C
static void compute_swaps(t_swapped_stack *stack, long start, long end)
{
	uint	first_value;
	uint	second_value;
	uint	third_value;

	if (stack->stack.len < 3)
		return ;
	start = (long)modulo(start, stack->stack.len);
	end = (long)modulo(end, stack->stack.len);
	stack_rotate(&stack->stack, (size_t)start);
	while (true)
	{
		first_value = stack_get_value(&stack->stack, 0);
		second_value = stack_get_value(&stack->stack, 1);
		third_value = stack_get_value(&stack->stack, 2);
		fprintf(stderr, "⚠️ start = %zu | offset = %zu => first = %u | second = %u | third = %u ", start, stack->stack.offset, first_value, second_value, third_value);
		if (first_value > second_value && first_value < third_value)
		{
			stack->swaps[first_value] = true;
			stack_swap(&stack->stack);
			if (start < 2)
				stack->first_swapped = true;
		}
		stack_reverse_rotate(&stack->stack, 1);
		fprintf(stderr, "=> swaps[%u] = %i\n", first_value, stack->swaps[first_value]);
		if (start == end)
			break ;
		start = (long)modulo(start - 1, stack->stack.len);
	}
	stack_reverse_rotate(&stack->stack, stack->stack.offset);
}

static void	free_all(t_lis *lis, t_swapped_stack *stack_1, t_swapped_stack *stack_2)
{
	if (lis && lis->keep)
		free(lis->keep);
	if (lis && lis->swap)
		free(lis->swap);
	if (stack_1 && stack_1->stack.data)
		free(stack_1->stack.data);
	if (stack_1 && stack_1->swaps)
		free(stack_1->swaps);
	if (stack_2 && stack_2->stack.data)
		free(stack_2->stack.data);
	if (stack_2 && stack_2->swaps)
		free(stack_2->swaps);
}
