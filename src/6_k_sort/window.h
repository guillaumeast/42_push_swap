#ifndef WINDOW_H
# define WINDOW_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_chunk
{
	size_t		size;
	size_t		capacity;
	uint		min;
	uint		med;
	uint		max;
	bool		*treated;
	size_t		treated_count;
}	t_window;

bool	window_init(t_window *window, size_t capacity, size_t size);
void	window_update(t_window *window, uint value, size_t stack_len);
void	window_free(t_window *window);

#endif
