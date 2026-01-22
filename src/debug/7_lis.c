#include "debug.h"
#include "lis.h"
#include <stdio.h>

static void	print_bool_array(bool *arr, size_t len);

void	lis_print(t_lis *lis, size_t len)
{
	fprintf(stderr, "🏹 LIS from [%zu])\n", lis->start_index);
	fprintf(stderr, "          => keep %3zu => ", lis->keep_count);
	print_bool_array(lis->keep, len);
	if (lis->swap)
	{
		fprintf(stderr, "          => swap %3zu => ", lis->swap_count);
		print_bool_array(lis->swap, len);
	}
	else
		fprintf(stderr, "          => no_swap\n");
}

static void	print_bool_array(bool *arr, size_t len)
{
	size_t	i;
	bool	first;

	fprintf(stderr, "[");
	first = true;
	i = 0;
	while (i < len)
	{
		if (arr[i])
		{
			if (!first)
				fprintf(stderr, ", ");
			fprintf(stderr, "%zu", i);
			first = false;
		}
		i++;
	}
	fprintf(stderr, "]\n");
}
