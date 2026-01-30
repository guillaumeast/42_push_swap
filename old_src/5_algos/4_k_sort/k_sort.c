#include "state.h"
#include "config.h"
#include "window.h"
#include "moves.h"
#include "swap.h"
#include "sort_three.h"
#include <stdlib.h>

# include "debug.h"
# include "print.h"

static bool	is_in_range(uint value, t_window *window);
static bool	exec(t_state *state, t_config *config, t_window *window);

// TODO: take a run as input instead of state and config (and don't take it as const !)
bool	k_sort(t_state *state, const t_config *config)
{
	t_window	window;
	size_t		index;
	t_config	mutable_cfg;

	// TODO: do not dup config anymore
	print_title("k_sort()");
	print_info("Initial stack      ⇢ ");
	if (should_print(LOG))
	{
		stack_print_line(&state->a, NULL, GREY);
		fprintf(stderr, "\n");
	}
	if (!config_dup(&mutable_cfg, config, state->a.len))
		return (false);
	print_pass("Config initialized ⇢ ");
	if (should_print(LOG))
		config_print(&mutable_cfg, 0, false);
	window_init(&window, state, &mutable_cfg);
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		index = 0;
		print_info("Searching...\n");
		while (!is_in_range(stack_get_value(&state->a, (long)index), &window))
			index++;
		print_info("Rotating...\n");
		if (index <= state->a.len / 2)
		{
			if (!ra(state, index))
				return (false);
		}
		else
			if (!rra(state, state->a.len - index))
				return (false);
		print_info("Executing...\n");
		if (!exec(state, &mutable_cfg, &window))
			return (print_error("exec() failed"), false);
	}
	config_free(&mutable_cfg);
	free(window.treated);
	print_result("k_sort done in %3zu moves", state->moves.len);
	return (sort_three(state, config));
}

static bool	is_in_range(uint value, t_window *window)
{
	// if (value >= window->min && value < window->max)
	// 	fprintf(stderr, "%s🅚     is_in_range(%s%u%s, [%u - %u]) = %strue%s\n", GREY, YELLOW, value, GREY, window->min, window->max, GREEN, NC);						// TODO: tmp debug
	// else
	// 	fprintf(stderr, "%s🅚     is_in_range(%s%u%s, [%u - %u]) = %sfalse%s\n", GREY, YELLOW, value, GREY, window->min, window->max, RED, NC);						// TODO: tmp debug
	// print_info("Checking %3u in range ⇢ ");
	// print_window(LOG, window, true);
	return (value >= window->min && value < window->max);
}

static bool	exec(t_state *state, t_config *config, t_window *window)
{
	uint	val;

	print_title("exec()");
	val = stack_get_value(&state->a, 0);
	if (config->opti_lis_swap && config->lis.swap[val])
	{
		print_info("swapping   %s%3u\n", YELLOW, val);
		if (!opti_swap_lis(state, config, val))
			return (false);
	}
	else if (config->opti_lis && config->lis.keep[val])
	{
		print_info("rotating A %s%3u\n", YELLOW, val);
		if (!ra(state, 1))
			return (false);
	}
	else
	{
		print_info("pushing    %s%3u\n", YELLOW, val);
		if (!pb(state, 1))
			return (false);
		if (val <= window->median.median)
		{
			print_info("rotating B %s%3u\n", YELLOW, val);
			if (!rb(state, 1))
				return (false);
		}
		if (config->opti_swap_b)
		{
			print_info("Calling opti_swap_b()\n");
			if (!opti_swap_b(state, config))
				return (false);
		}
	}
	window_update(val, config, window, state->a.len);
	print_result("executed");
	return (true);
}

