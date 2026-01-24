#include "libft.h"
#include "stack.h"
#include <stdlib.h>

#define CHUNK_N_MIN 2
#define CHUNK_N_MAX 9

bool	get_chunk_sizes(size_t **ret, size_t *ret_size, const t_stack *stack)
{
	size_t	max_size;
	long	size;
	size_t	i;
	size_t	n;

	max_size = (CHUNK_N_MAX - CHUNK_N_MIN + 1) * 2;
	*ret = malloc(max_size * sizeof ** ret);
	if (!*ret)
		return (false);
	i = 0;
	n = CHUNK_N_MIN;
	while (n <= CHUNK_N_MAX)
	{
		size = (long)(stack->len / n);
		if (size > 0)
			(*ret)[i++] = (size_t)size;
		size = (long)n * (long)square_root_rounded((int)stack->len);
		if (size > 0)
			(*ret)[i++] = (size_t)size;
		n++;
	}
	*ret_size = i;
	return (true);
}
