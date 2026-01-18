#ifndef MEDIAN_H
# define MEDIAN_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_median
{
	size_t	total_count;	// Total of values
	size_t	left_count;		// Count of values <= median
	bool	*present;		// Array of values (1 if present, 0 otherwise)
	uint	median;			// Median value
}	t_median;

bool	median_init(t_median *median, size_t values_count);
void	median_update(t_median *median, uint new_value);
void	median_free(t_median *median);

#endif
