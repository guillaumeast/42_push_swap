#ifndef WINDOW_H
# define WINDOW_H

# include "state.h"
# include "config.h"
# include "median.h"

typedef struct s_chunk
{
	size_t		size;
	size_t		capacity;
	uint		min;
	uint		max;
	bool		*treated;
	size_t		treated_count;
	t_median	median;
}	t_window;

bool	window_init(t_window *window, t_state *state, const t_config *config);
void	window_update(uint value, const t_config *config, t_window *window, size_t stack_len);

#endif
