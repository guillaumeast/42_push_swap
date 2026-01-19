#include "libft.h"
#include "config_priv.h"
#include <stdlib.h>

#define CHUNK_N_MIN 2
#define CHUNK_N_MAX 9

static void	chunk_init(t_chunk *chunk, size_t values_count, t_chunk_type type, size_t n);

// Caller must free chunks->data
bool	chunk_generate(t_chunk_list *chunks, size_t values_count)
{
	t_chunk	*chunk_list;
	size_t	i;
	size_t	n;

	chunks->count = (CHUNK_N_MAX - CHUNK_N_MIN + 1) * 2;
	chunk_list = malloc(chunks->count * sizeof * chunk_list);
	if (!chunk_list)
		return (false);
	i = 0;
	n = CHUNK_N_MIN;
	while (n <= CHUNK_N_MAX)
	{
		chunk_init(&chunk_list[i], values_count, DIVISION, n);
		i++;
		chunk_init(&chunk_list[i], values_count, SQUARE_ROOT, n);
		i++;
		n++;
	}
	return (true);
}

static void	chunk_init(t_chunk *chunk, size_t values_count, t_chunk_type type, size_t n)
{
	if (type == DIVISION)
		chunk->size = (uint)(values_count / n);
	else
		chunk->size = (uint)n * (uint)square_root_rounded((int)values_count);
	chunk->min = 0;
	chunk->max = chunk->min + chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
	chunk->treated = 0;
}
