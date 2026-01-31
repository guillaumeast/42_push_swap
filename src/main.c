/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:10:12 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/31 14:08:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "state.h"
#include "moves.h"
#include "k_sort.h"
#include "sort_three.h"
#include "greedy.h"
#include "finish.h"
#include <stdlib.h>
#include <unistd.h>

static bool	run_algos(t_state *state);
static int	free_and_print_error(t_state *state);

int	main(int argc, char **argv)
{
	t_args		args;
	t_state		state;

	if (argc < 2)
		return (0);
	if (!args_parse(argc, argv, &args))
		return (free_and_print_error(NULL));
	if (!state_init(&state, args.values, args.count))
		return (free(args.values), free_and_print_error(NULL));
	if (!run_algos(&state))
		return (free_and_print_error(&state));
	if (!moves_print(&state.moves))
		return (free_and_print_error(&state));
	state_free(&state);
	return (0);
}

static bool	run_algos(t_state *state)
{
	if (state->a.len < 150)
	{
		if (!pb(state, state->a.len - 3))
			return (false);
	}
	else if (!k_sort(state))
		return (false);
	if (!sort_three(state))
		return (false);
	if (!greedy(state))
		return (false);
	if (!finish(state))
		return (false);
	optimize_moves(&state->moves);
	return (true);
}

static int	free_and_print_error(t_state *state)
{
	if (state)
		state_free(state);
	(void)write(2, "Error\n", 6);
	return (EXIT_FAILURE);
}
