#include "libft.h"
#include "config_priv.h"
#include <stdlib.h>

#define CHUNK_N_MIN 2
#define CHUNK_N_MAX 9

typedef enum e_chunk_type
{
	DIVISION,
	SQUARE_ROOT
}	t_chunk_type;

static bool	chunk_init(t_chunk *chunk, size_t values_count, t_chunk_type type, size_t n);

// Caller must free chunks->data
bool	generate_chunks(t_chunk_list *chunks, size_t values_count)
{
	size_t	i;
	size_t	n;

	chunks->count = (CHUNK_N_MAX - CHUNK_N_MIN + 1) * 2;
	chunks->data = malloc(chunks->count * sizeof * chunks->data);
	if (!chunks->data)
		return (false);
	i = 0;
	n = CHUNK_N_MIN;
	while (n <= CHUNK_N_MAX)
	{
		if (chunk_init(&chunks->data[i], values_count, DIVISION, n))
			i++;
		else
		 	chunks->count--;
		if (chunk_init(&chunks->data[i], values_count, SQUARE_ROOT, n))
			i++;
		else
		 	chunks->count--;
		n++;
	}
	return (true);
}

static bool	chunk_init(t_chunk *chunk, size_t values_count, t_chunk_type type, size_t n)
{
	if (type == DIVISION)
		chunk->size = (uint)(values_count / n);
	else
		chunk->size = (uint)n * (uint)square_root_rounded((int)values_count);
	chunk->min = 0;
	chunk->max = chunk->min + chunk->size;
	chunk->median = (chunk->min + chunk->max) / 2;
	chunk->treated = 0;
	return (chunk->size > 0);
}
