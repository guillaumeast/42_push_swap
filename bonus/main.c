/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:04:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/31 14:20:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "args.h"
#include "state.h"
#include "stack_ops.h"
#include <stdlib.h>
#include <unistd.h>

#define MOVE_CAP 24000	// = 6000 * 4

static bool	exec_instructions(t_state *state, const t_buff *input);
static bool	execute_move(t_state *state, char *move);
static bool	handle_combined_moves(t_state *state, char *move);
static int	print_error(void);

int	main(int argc, char **argv)
{
	t_args	args;
	t_state	state;
	t_buff	input;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (!args_parse(argc, argv, &args))
		return (print_error());
	if (!state_init(&state, args.values, args.count))
		return (free(args.values), print_error());
	if (!buff_init(&input, MOVE_CAP * sizeof(char)))
		return (state_free(&state), print_error());
	if (!buff_read_all(&input, STDIN_FILENO))
		return (buff_free(&input), state_free(&state), print_error());
	if (!exec_instructions(&state, &input))
		return (buff_free(&input), state_free(&state), print_error());
	else if (!stack_is_sorted(&state.a)
		|| stack_get_value(&state.a, 0) != 0 || state.b.len != 0)
		(void)write(1, "KO\n", 3);
	else
		(void)write(1, "OK\n", 3);
	state_free(&state);
	buff_free(&input);
	return (EXIT_SUCCESS);
}

// split problem => can't detect empty lines
static bool	exec_instructions(t_state *state, const t_buff *input)
{
	size_t	i;
	long	len;
	char	*start;
	char	*end;

	i = 0;
	while (i < input->len)
	{
		start = input->data + i;
		end = str_chr(start, '\n');
		if (!end)
			return (false);
		len = end - start;
		if (len < 2 || len > 3)
			return (false);
		if (!execute_move(state, start))
			return (false);
		i += (size_t)len + 1;
	}
	return (true);
}

static bool	execute_move(t_state *state, char *move)
{
	if (str_ncmp("ra\n", move, 3) == 0)
		return (stack_rotate(&state->a, 1), true);
	else if (str_ncmp("rb\n", move, 3) == 0)
		return (stack_rotate(&state->b, 1), true);
	else if (str_ncmp("rra\n", move, 4) == 0)
		return (stack_reverse_rotate(&state->a, 1), true);
	else if (str_ncmp("rrb\n", move, 4) == 0)
		return (stack_reverse_rotate(&state->b, 1), true);
	else if (str_ncmp("sa\n", move, 3) == 0)
		return (stack_swap(&state->a), true);
	else if (str_ncmp("sb\n", move, 3) == 0)
		return (stack_swap(&state->b), true);
	else if (str_ncmp("pa\n", move, 3) == 0)
		return (stack_push(&state->b, &state->a, 1), true);
	else if (str_ncmp("pb\n", move, 3) == 0)
		return (stack_push(&state->a, &state->b, 1), true);
	return (handle_combined_moves(state, move));
}

static bool	handle_combined_moves(t_state *state, char *move)
{
	if (str_ncmp("rr\n", move, 3) == 0)
	{
		stack_rotate(&state->a, 1);
		stack_rotate(&state->b, 1);
	}
	else if (str_ncmp("rrr\n", move, 4) == 0)
	{
		stack_reverse_rotate(&state->a, 1);
		stack_reverse_rotate(&state->b, 1);
	}
	else if (str_ncmp("ss\n", move, 3) == 0)
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
	(void)write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
