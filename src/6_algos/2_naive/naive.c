#include "naive.h"
#include "sort_three.h"
#include "moves.h"
#include "median.h"
#include "lis.h"
#include "swap.h"
# include "debug.h"

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

	size_t	i = 0, imax = 10;
	while (i < imax && !stack_is_sorted(&state->a))
	{
		value = stack_get_value(&state->a, 0);
		// fprintf(stderr, "\n%spush_to_b()%s => %s", YELLOW, NC, BLUE);
		// config_print(config, 0, false);
		// if (config->opti_lis_swap)
		// {
		// 	fprintf(stderr, "%s            => swap = ", NC);
		// 	print_bool_array(config->lis.swap, NULL, state->a.len + state->b.len, NC);
		// 	fprintf(stderr, "\n");
		// }
		// fprintf(stderr, "           %s => %s", NC, YELLOW);
		// stack_print_line(&state->a, NULL, YELLOW);
		// fprintf(stderr, "%s => %s%u%s\n", NC, YELLOW, value, NC);
		if (config->opti_lis_swap && config->lis.swap[value])
		{
			// fprintf(stderr, "            => %sswap%s   => calling opti_swap_lis()...\n", BLUE, NC);
			if (!opti_swap_lis(state, config, value))
				return (false);
		}
		else if (config->opti_lis && config->lis.keep[value])
		{
			// fprintf(stderr, "            => %skeep%s   => calling ra()...\n", GREEN, NC);
			if (!ra(state, 1))
				return (false);
		}
		else
		{
			// fprintf(stderr, "            => %spush%s   => calling pb()...\n", RED, NC);
			if (!pb(state, 1))
				return (false);
			if (config->opti_median)
			{
				// fprintf(stderr, "            => %smedian%s => calling opti_median()...\n", GREY, NC);
				if (!opti_median(state, median, value))
					return (false);
			}
			if (config->opti_swap_b)
			{
				// fprintf(stderr, "            => %sswap_b%s => calling opti_swap_b()...\n", GREY, NC);
				if (!opti_swap_b(state, config))
					return (false);
			}
		}
		// if (stack_is_sorted(&state->a))
			// fprintf(stderr, "            => stack_is_sorted(&state->a) = %strue%s\n", GREEN, NC);
		// else
			// fprintf(stderr, "            => stack_is_sorted(&state->a) = %sfalse%s\n", RED, NC);
		// if (config->opti_lis_swap && config->lis.swap_count > 0)
		// 	fprintf(stderr, "(config->opti_lis_swap && config->lis.swap_count > 0) = %strue%s\n", GREEN, NC);
		// else
		// 	fprintf(stderr, "(config->opti_lis_swap && config->lis.swap_count > 0) = %sfalse%s\n", RED, NC);
		i++;
	}
	return (true);
}
