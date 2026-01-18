#ifndef CHUNK_PRIVATE_H
# define CHUNK_PRIVATE_H

# include <sys/types.h>

typedef struct s_chunk
{
	uint	size;
	uint	min;
	uint	max;
	uint	median;
	size_t	treated;
}	t_chunk;

#endif
