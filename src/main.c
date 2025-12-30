/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:03:39 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/30 17:32:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	free_and_exit(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &a, &b))
		free_and_exit(&a, &b);
	if (!stack_convert_to_sorted_indexes(&a))
		free_and_exit(&a, &b);
	if (!step_1(&a, &b))
		free_and_exit(&a, &b);
	if (b.count > 0 || !is_sorted(&a))
	{
		if (!step_2(&a, &b))
			free_and_exit(&a, &b);
	}
	finish(&a, &b);
	stack_free(&a, &b);
	return (0);
}

bool	is_sorted(t_stack *stack)
{
	size_t	i;
	int		breaks;

	breaks = 0;
	i = 0;
	while (i < stack->count)
	{
		if (stack->values[i] > stack->values[(i + 1) % stack->count])
			breaks++;
		i++;
	}
	return (breaks <= 1);
}

bool	finish(t_stack *a, t_stack *b)
{
	size_t	zero_index;

	if (b->count > 0 || !is_sorted(a))
		return (false);
	zero_index = 0;
	while (a->values[zero_index] != 0)
		zero_index++;
	if (zero_index <= a->count / 2)
	{
		while (a->values[0] != 0)
			rotate(a, b, A);
	}
	else
	{
		while (a->values[0] != 0)
			rotate_reverse(a, b, A);
	}
	return (true);
}

static void	free_and_exit(t_stack *a, t_stack *b)
{
	stack_free(a, b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
