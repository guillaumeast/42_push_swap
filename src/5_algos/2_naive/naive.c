#include "naive.h"
#include "sort_three.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include "swap.h"
# include "debug.h"
# include <print.h>	// TMP: remove before submit

static bool	push_to_b(t_state *state, t_config *config, t_median *median);

bool	naive(t_state *state, const t_config *config)
{
	t_median	median;
	t_config	cfg;
	
	if (!config->opti_swap_b && !config->opti_median && !config->opti_lis)
		return (pb(state, state->a.len - 3) && sort_three(state, config));
	// NOTE: NULL in case of premature free when push_to_b() fails
	median.present = NULL;
	if (config->opti_median && !median_init(&median, state->a.len))
		return (false);
	if (!config_dup(&cfg, config, state->a.len))
		return (median_free(&median), false);
	if (!push_to_b(state, &cfg, &median))
		return (median_free(&median), config_free(&cfg), false);
	if (config->opti_median)
		median_free(&median);
	config_free(&cfg);
	return (sort_three(state, config));
}

static bool	push_to_b(t_state *state, t_config *config, t_median *median)
{
	uint	value;
	bool	print_logs;

	print_logs = false;	// TMP: remove before submit
	if (print_logs)
		stack_print(&state->a, &state->b);
	// size_t i = 0;
	// while (i < 10 && !stack_is_sorted(&state->a))
	while (state->a.len > 3 && !stack_is_sorted(&state->a))
	{
		value = stack_get_value(&state->a, 0);
		if (print_logs)
		{
			// i++;
			fprintf(stderr, "\n%spush_to_b()%s => %s", YELLOW, NC, BLUE);
			config_print(config, 0, false);
			if (config->opti_lis_swap)
			{
				fprintf(stderr, "%s            => swap     => ", NC);
				print_bool_array(config->lis.swap, NULL, state->a.len + state->b.len, NC);
				fprintf(stderr, "\n");
			}
			if (config->opti_lis)
			{
				fprintf(stderr, "           %s => lis      => %s", NC, YELLOW);
				print_bool_array(config->lis.keep, NULL, state->a.len + state->b.len, GREEN);
				fprintf(stderr, "\n");
			}
			fprintf(stderr, "           %s => stack    => %s", NC, YELLOW);
			stack_print_line(&state->a, NULL, YELLOW);
			fprintf(stderr, "%s\n", NC);
		}
		if (config->opti_lis_swap && config->lis.swap[value])
		{
			if (print_logs)
				fprintf(stderr, "            => %sswap %s%3u%s => calling opti_swap_lis()...\n", BLUE, YELLOW, value, NC);
			if (!opti_swap_lis(state, config, value))
				return (false);
		}
		else if (config->opti_lis && config->lis.keep[value])
		{
			if (print_logs)
			{
				fprintf(stderr, "           %s => lis      => %s", NC, YELLOW);
				print_bool_array(config->lis.keep, NULL, state->a.len + state->b.len, GREEN);
				fprintf(stderr, "\n            => %skeep %s%3u%s => calling ra()...\n", GREEN, YELLOW, value, NC);
			}
			if (!ra(state, 1))
				return (false);
		}
		else
		{
			if (print_logs)
				fprintf(stderr, "            => %spush %s%3u%s => calling pb()...\n", RED, YELLOW, value, NC);
			if (!pb(state, 1))
				return (false);
			if (config->opti_median)
			{
				if (print_logs)
					fprintf(stderr, "            => %smedian%s   => calling opti_median()...\n", GREY, NC);
				if (!opti_median(state, median, value))
					return (false);
			}
			if (config->opti_swap_b)
			{
				if (print_logs)
					fprintf(stderr, "            => %sswap_b%s   => calling opti_swap_b()...\n", GREY, NC);
				if (!opti_swap_b(state, config))
					return (false);
			}
		}
		if (print_logs)
		{
			if (stack_is_sorted(&state->a))
				fprintf(stderr, "            => %ssorted() => true%s\n", GREEN, NC);
			else
				fprintf(stderr, "            => %ssorted() => false%s\n", RED, NC);
		}
	}
	return (true);
}
