#include "state.h"
#include "config.h"
#include "median.h"
#include "moves.h"
#include "swap.h"
#include "sort_three.h"
#include <stdlib.h>
# include "debug.h"

typedef struct s_chunk
{
	size_t		size;
	size_t		capacity;
	uint		min;
	uint		max;
	bool		*treated;
	size_t		treated_count;
	t_median	median;
}	t_chunk;

static bool	init_window(t_chunk *window, t_state *state, const t_config *config);
static bool	is_in_range(uint value, t_chunk *window);
static bool	exec(t_state *state, t_config *config, t_chunk *window);
static void	update_window(uint value, const t_config *config, t_chunk *window);

bool	k_sort(t_state *state, const t_config *config)
{
	t_chunk		window;
	size_t		index;
	t_config	mutable_cfg;

	if (!config_dup(&mutable_cfg, config, state->a.len))
		return (false);
	init_window(&window, state, &mutable_cfg);
	while (!stack_is_sorted(&state->a))
	{
		index = 0;
		// fprintf(stderr, "%s🅚     Searching...%s\n", GREY, NC);						// TODO: tmp debug
		while (!is_in_range(stack_get_value(&state->a, (long)index), &window))
			index++;
		// fprintf(stderr, "%s🅚     Rotating...%s\n", GREY, NC);						// TODO: tmp debug
		if (index <= state->a.len / 2)
		{
			if (!ra(state, index))
				return (false);
		}
		else
			if (!rra(state, state->a.len - index))
				return (false);
		exec(state, &mutable_cfg, &window);
	}
	config_free(&mutable_cfg);
	free(window.treated);
	return (sort_three(state, config));
}

static bool	init_window(t_chunk *window, t_state *state, const t_config *config)
{
	window->capacity = state->a.len;
	window->size = config->chunk_size;
	window->min = 0;
	window->max = (uint)window->size;
	window->treated_count = 0;
	if (!median_init(&window->median, window->capacity))
		return (false);
	window->treated = malloc(window->capacity * sizeof * window->treated);
	if (!window->treated)
		return (median_free(&window->median), false);
	ft_memset(window->treated, false, state->a.len * sizeof * window->treated);
	return (true);
}

static bool	is_in_range(uint value, t_chunk *window)
{
	// if (value >= window->min && value < window->max)
	// 	fprintf(stderr, "%s🅚     is_in_range(%s%u%s, [%u - %u]) = %strue%s\n", GREY, YELLOW, value, GREY, window->min, window->max, GREEN, NC);						// TODO: tmp debug
	// else
	// 	fprintf(stderr, "%s🅚     is_in_range(%s%u%s, [%u - %u]) = %sfalse%s\n", GREY, YELLOW, value, GREY, window->min, window->max, RED, NC);						// TODO: tmp debug
	return (value >= window->min && value < window->max);
}

static bool	exec(t_state *state, t_config *config, t_chunk *window)
{
	uint	val;

	val = stack_get_value(&state->a, 0);
	// fprintf(stderr, "%s🅚 %s%3u%s Processing...%s\n", GREY, YELLOW, val, GREY, NC);						// TODO: tmp debug
	if (config->opti_lis_swap && config->lis.swap[val])
	{
		// fprintf(stderr, "%s🅚 %s%3u %sopti_swap_lis()%s\n", BLUE, YELLOW, val, BLUE, NC);				// TODO: tmp debug
		if (!opti_swap_lis(state, config, val))
			return (false);
	}
	else if (config->opti_lis && config->lis.keep[val])
	{
		// fprintf(stderr, "%s🅚 %s%3u %sra()%s\n", GREEN, YELLOW, val, GREEN, NC);				// TODO: tmp debug
		if (!ra(state, 1))
			return (false);
	}
	else
	{
		// fprintf(stderr, "%s🅚 %s%3u %spb()%s\n", RED, YELLOW, val, RED, NC);				// TODO: tmp debug
		if (!pb(state, 1))
			return (false);
		if (config->opti_median && val < window->median.median)
		{
			// fprintf(stderr, "%s🅚 %s%3u %srb()%s\n", BLUE, YELLOW, val, BLUE, NC);				// TODO: tmp debug
			if (!rb(state, 1))
				return (false);
		}
		if (config->opti_swap_b)
		{
			// fprintf(stderr, "%s🅚 %s%3u %sopti_swap_b()%s\n", BLUE, YELLOW, val, BLUE, NC);				// TODO: tmp debug
			if (!opti_swap_b(state, config))
				return (false);
		}
	}
	update_window(val, config, window);
	// fprintf(stderr, "\n");
	return (true);
}

static void	update_window(uint value, const t_config *config, t_chunk *window)
{
	if (window->treated[value])
		return ;
	window->treated[value] = true;
	window->treated_count++;
	window->size++;
	window->max++;
	if (config->opti_median)
		median_update(&window->median, value);	// version: median(window)
	else
		window->median.median++;									// version: treshold
	// TODO: minimize window sometimes...
	// fprintf(stderr, "%s🅚 %s%3u%s => window = min %u | med = %u | max = %u | treated = %zu / %zu%s\n", 
	// 	GREY, YELLOW, value, GREY, window->min, window->median.median, window->max, window->treated_count, window->size, NC);	// TODO: tmp debug
}
