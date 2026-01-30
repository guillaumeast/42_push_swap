#include "libft.h"
#include "window.h"
#include <stdlib.h>

bool	window_init(t_window *window, size_t capacity, size_t size)
{
	window->capacity = capacity;
	window->size = size;
	window->min = 0;
	window->med = 0;
	window->max = (uint)window->size;
	window->treated_count = 0;
	window->treated = malloc(window->capacity * sizeof * window->treated);
	if (!window->treated)
		return (false);
	ft_memset(window->treated, false, capacity * sizeof * window->treated);
	return (true);
}

void	window_update(t_window *window, uint value, size_t stack_len)
{
	if (window->treated[value])
		return ;
	window->treated[value] = true;
	window->treated_count++;
	if (window->treated_count > stack_len && window->size > stack_len / 6 && window->size > 50)
		window->size--;
	else
		window->max++;
	window->med++;
}

void	window_free(t_window *window)
{
	if (window && window->treated)
		free(window->treated);
}
