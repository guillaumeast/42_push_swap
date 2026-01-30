#ifndef CHUNK_H
# define CHUNK_H

# include "state.h"
# include "config.h"

typedef struct s_chunk
{
	size_t	size;
	uint	min;
	uint	max;
	uint	median;
	bool	*treated;
	size_t	treated_count;
}	t_chunk;

bool	chunk(t_state *state, const t_config *config);

#endif
