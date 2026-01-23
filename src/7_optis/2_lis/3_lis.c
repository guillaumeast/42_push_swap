#include "libft.h"
#include "lis_priv.h"
#include "stack_ops.h"
#include <stdlib.h>
# include "debug.h"	// TMP: remove before submit

// TODO: compute swaps backward !!

static bool	set_stack_1(t_swapped_stack *dst, t_stack *src);
static bool	set_stack_2(t_stack *stk, t_swapped_stack *v1, t_swapped_stack *v2);
static void compute_swaps(t_swapped_stack *stack, long start, size_t iter, bool backward);
static void	free_all(t_lis *lis, t_swapped_stack *stack_1, t_swapped_stack *stack_2);

bool	lis_compute_both(t_stack *stack, t_lis *lis, t_lis *lis_swap)
{
	t_swapped_stack	stack_1;
	t_swapped_stack	stack_2;

	log_debug("lis_compute_both", 0, "Starting...\n");
	if (!lis_best(stack, NULL, lis))
		return (false);
	if (!set_stack_1(&stack_1, stack))
		return (free_all(lis, NULL, NULL), false);
	compute_swaps(&stack_1, 0, stack->len, false);
	log_debug("lis_compute_both", 0, "stack_1->swaps = ");
	print_bool_array(stack_1.swaps, stack_1.stack.len);
	stack_print(stack, &stack_1.stack);
	if (stack_1.first_swapped)
	{
		log_debug("lis_compute_both", 0, "Setting stack_2...\n");
		if (!set_stack_2(stack, &stack_1, &stack_2))
			return (free_all(lis, &stack_1, NULL), false);
		log_debug("lis_compute_both", 0, "Computing swaps...\n");
		compute_swaps(&stack_1, (long)stack->len - 2, stack->len, false);
		log_debug("lis_compute_both", 0, "stack_2->swaps = ");
		print_bool_array(stack_2.swaps, stack->len);
		stack_print(stack, &stack_1.stack);
		if (!lis_best_between(&stack_1, &stack_2, lis_swap))
			return (free_all(lis, &stack_1, &stack_2), false);
		fprintf(stderr, "\n");
		log_debug("lis_compute_both", 0, "RESULTS:\n");
		lis_print(lis, stack->len);
		lis_print(lis_swap, stack->len);
		return (free_all(NULL, &stack_1, &stack_2), true);
	}
	else if (!lis_best(&stack_1.stack, stack_1.swaps, lis_swap))
		return (free_all(lis, &stack_1, NULL), false);
	fprintf(stderr, "\n");
	log_debug("lis_compute_both", 0, "RESULTS:\n");
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
static void compute_swaps(t_swapped_stack *stack, long start, size_t iter, bool backward)
{
	// size_t	i;
	// size_t	index;
	// size_t	next_index;
	// uint	tmp;

	(void)stack;
	(void)start;
	(void)iter;
	(void)backward;

	// if (stack->stack.len <= 3)	// NOTE: sort_three() will handle it
	// 	return ;
	// i = 0;
	// while (i <= iter)
	// {
	// 	if (backward)	// TODO: doesn't work ??
	// 		index = modulo(start - (long)i, stack->stack.len);
	// 	else
	// 		index = modulo(start + (long)i, stack->stack.len);
	// 	next_index = modulo((long)index + 1, stack->stack.len);
	// 	if (should_swap(&stack->stack, index, stack_get_value(&stack->stack, (long)index), 0))
	// 	{
	// 		stack->swaps[stack->stack.data[index]] = true;
	// 		tmp = stack->stack.data[index];
	// 		stack->stack.data[index] = stack->stack.data[next_index];
	// 		stack->stack.data[next_index] = tmp;
	// 		// fprintf(stderr, "👉 [%zu] => [%u %u %u] \n\n", 
	// 		// 	index, 
	// 		// 	stack->stack.data[index], 
	// 		// 	stack->stack.data[next_index], 
	// 		// 	stack->stack.data[modulo((long)next_index + 1, stack->stack.len)]);
	// 		i += 2;
	// 	}
	// 	else
	// 		i++;
	// }
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
