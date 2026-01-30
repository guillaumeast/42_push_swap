/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:52:03 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 19:52:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "args.h"
#include "state.h"
#include "stack_ops.h"
#include <stdlib.h>
#include <unistd.h>

static void	read_and_execute_instructions(t_state *state);
static void	execute_move(t_state *state, t_buff *move);
static bool	handle_combined_moves(t_state *state, t_buff *move);
static int	print_error(void);

int	main(int argc, char **argv)
{
	t_args	args;
	t_state	state;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (!args_parse(argc, argv, &args))
		return (print_error());
	if (!state_init(&state, args.values, args.count))
		return (free(args.values), print_error());
	read_and_execute_instructions(&state);
	if (stack_is_sorted(&state.a) && stack_get_value(&state.a, 0) == 0
		&& state.b.len == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	state_free(&state);
	return (EXIT_SUCCESS);
}

static void	read_and_execute_instructions(t_state *state)
{
	t_buff	*move;

	move = get_next_chunk(0, '\n');
	while (move)
	{
		execute_move(state, move);
		buff_free(move);
		free(move);
		move = get_next_chunk(0, '\n');
	}
}

static void	execute_move(t_state *state, t_buff *move)
{
	if (handle_combined_moves(state, move))
		return ;
	else if (str_ncmp("ra\n", move->data, move->len) == 0)
		stack_rotate(&state->a, 1);
	else if (str_ncmp("rb\n", move->data, move->len) == 0)
		stack_rotate(&state->b, 1);
	else if (str_ncmp("rra\n", move->data, move->len) == 0)
		stack_reverse_rotate(&state->a, 1);
	else if (str_ncmp("rrb\n", move->data, move->len) == 0)
		stack_reverse_rotate(&state->b, 1);
	else if (str_ncmp("sa\n", move->data, move->len) == 0)
		stack_swap(&state->a);
	else if (str_ncmp("sb\n", move->data, move->len) == 0)
		stack_swap(&state->b);
	else if (str_ncmp("pa\n", move->data, move->len) == 0)
		stack_push(&state->b, &state->a, 1);
	else if (str_ncmp("pb\n", move->data, move->len) == 0)
		stack_push(&state->a, &state->b, 1);
}

static bool	handle_combined_moves(t_state *state, t_buff *move)
{
	if (str_ncmp("rr\n", move->data, move->len) == 0)
	{
		stack_rotate(&state->a, 1);
		stack_rotate(&state->b, 1);
	}
	else if (str_ncmp("rrr\n", move->data, move->len) == 0)
	{
		stack_reverse_rotate(&state->a, 1);
		stack_reverse_rotate(&state->b, 1);
	}
	else if (str_ncmp("ss\n", move->data, move->len) == 0)
	{
		stack_swap(&state->a);
		stack_swap(&state->b);
	}
	else
		return (false);
	return (true);
}

static int	print_error(void)
{
	write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
