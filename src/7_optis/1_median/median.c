#include "libft.h"
#include "median.h"
#include "moves.h"
#include <stdlib.h>
// # include "debug.h"

static void	update(t_median *median);

bool	median_init(t_median *median, size_t values_count)
{
	median->present = malloc(values_count * sizeof * median->present);
	if (!median->present)
		return (false);
	ft_memset(median->present, false, values_count * sizeof * median->present);
	median->total_count = 0;
	median->left_count = 0;
	median->median = 0;
	return (true);
}

void	median_update(t_median *median, uint new_value)
{
	// fprintf(stderr, "%smedian_update()%s => value = %s%u%s\n", YELLOW, NC, YELLOW, new_value, NC);
	if (median->present[new_value])
		return ;
	median->total_count++;
	if (median->total_count == 1)
	{
		median->left_count++;
		median->median = new_value;
	}
	else if (new_value < median->median)
		median->left_count++;
	median->present[new_value] = true;
	update(median);
	// fprintf(stderr, "%smedian_update()%s updated => median = %s%u%s\n", YELLOW, NC, YELLOW, median->median, NC);
}

static void	update(t_median *median)
{
	if (median->left_count < (median->total_count / 2) + 1)
	{
		median->median++;
		median->left_count++;
		// fprintf(stderr, "%supdate()%s => accessing present[%u] (+) ...\n", YELLOW, NC, median->median);
		while (!median->present[median->median])
			median->median++;
	}
	else if (median->left_count - 1 > median->total_count / 2)
	{
		median->median--;
		median->left_count--;
		// fprintf(stderr, "%supdate()%s => accessing present[%u] (-) ...\n", YELLOW, NC, median->median);
		while (!median->present[median->median])
			median->median--;
	}
	// fprintf(stderr, "%supdate()%s => median = %s%u%s, left_count = %zu, total = %zu => present = ", YELLOW, NC, YELLOW, median->median, NC, median->left_count, median->total_count);
	// print_bool_array(median->present, NULL, 5, NC);
	// fprintf(stderr, "\n");
}

bool	opti_median(t_state *state, t_median *median, uint value)
{
	median_update(median, value);
	if (value < median->median)
		return (rb(state, 1));
	return (true);
}

void	median_free(t_median *median)
{
	if (median->present)
		free(median->present);
}

