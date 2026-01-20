#include "debug.h"
#include "lis.h"
#include <stdio.h>

static void	print_bool_array(bool *arr, size_t len, const char *label);

void	lis_print(t_state *state, t_lis *lis)
{
	size_t	len;

	len = state->a.len + state->b.len;
	fprintf(stderr, "\n[🔦 DEBUG] len = %zu\n", len);
	fprintf(stderr, "🏹 LIS (starting at index %zu)\n", lis->start_index);
	print_bool_array(lis->keep, lis->keep_count, "KEEP");
	print_bool_array(lis->swap, len, "SWAP");
}

static void	print_bool_array(bool *arr, size_t len, const char *label)
{
	size_t	i;
	bool	first;

	fprintf(stderr, "    => %s = [", label);
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
