#include "libft.h"
#include "median.h"
#include <stdlib.h>

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
	median->total_count++;
	if (median->total_count == 1)
	{
		median->left_count++;
		median->median = new_value;
		median->present[new_value] = true;
	}
	else
	{
		median->present[new_value] = true;
		if (new_value < median->median)
			median->left_count++;
	}
	update(median);
}

static void	update(t_median *median)
{
	if (median->left_count < (median->total_count / 2) + 1)
	{
		median->median++;
		median->left_count++;
		while (!median->present[median->median])
			median->median++;
	}
	else if (median->left_count - 1 > median->total_count / 2)
	{
		median->median--;
		median->left_count--;
		while (!median->present[median->median])
			median->median--;
	}
}

void	median_free(t_median *median)
{
	free(median->present);
}

