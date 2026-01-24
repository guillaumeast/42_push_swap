#include "debug.h"
#include "lis.h"
#include <stdio.h>

void	lis_print(const t_lis *lis, size_t len)
{
	fprintf(stderr, "🏹 LIS from [%zu]:\n", lis->start_index);
	fprintf(stderr, "          => keep %3zu => ", lis->keep_count);
	print_bool_array(lis->keep, NULL, len, NC);
	if (lis->swap)
	{
		fprintf(stderr, "          => swap %3zu => ", lis->swap_count);
		print_bool_array(lis->swap, NULL, len, NC);
	}
	else
		fprintf(stderr, "          => no_swap\n");
}

void	print_bool_array(const bool *arr, const bool *versus, size_t len, const char *color)
{
	size_t	i;
	bool	first;

	fprintf(stderr, "%s[", color);
	first = true;
	i = 0;
	while (i < len)
	{
		if (arr[i])
		{
			if (!first)
				fprintf(stderr, ", ");
			if (versus && !versus[i])
				fprintf(stderr, "%s%zu%s", YELLOW, i, color);
			else
				fprintf(stderr, "%zu", i);
			first = false;
		}
		i++;
	}
	fprintf(stderr, "]%s", NC);
}
