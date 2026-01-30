#include "window.h"
#include "median.h"
#include <stdlib.h>

// TMP: remove before submit
# include "print.h"
static void	print_window(t_style style, t_window *window, bool new_line);

bool	window_init(t_window *window, t_state *state, const t_config *config)
{
	print_title("window_init()");
	window->capacity = state->a.len;
	window->size = config->chunk_size;
	window->min = 0;
	window->max = (uint)window->size;
	window->treated_count = 0;
	if (!median_init(&window->median, window->capacity))
		return (false);
	window->treated = malloc(window->capacity * sizeof * window->treated);
	if (!window->treated)
		return (median_free(&window->median), false);
	ft_memset(window->treated, false, state->a.len * sizeof * window->treated);
	print_result_mid(false, "window initialized %s⇢ ", GREY);
	print_window(RESULT, window, true);
	print_result_bot(true);
	return (true);
}

void	window_update(uint value, const t_config *config, t_window *window, size_t stack_len)
{
	print_title("window_update()");
	if (window->treated[value])
		return ;
	window->treated[value] = true;
	window->treated_count++;
	// Best so far : 3 487 - 3 751 - 3 872
	// if (window->treated_count > stack_len && window->size > stack_len / 3 && window->size > 5)
	// if (window->size > stack_len / 4 && window->size > 50)
	if (window->treated_count > stack_len && window->size > stack_len / 6 && window->size > 50)
	{
		print_warn("window slide freezed ❄️ ⇢ ");
		print_window(LOG, window, true);
		window->size--;
	}
	else
		window->max++;
	if (config->opti_median)
		median_update(&window->median, value);	// version: median(window)
	// else if (window->treated_count > stack_len && window->treated_count % 2 == 0)
	// 	window->median.median += 2;									// version: treshold
	else
		window->median.median++;									// version: treshold
	print_result_mid(false, "window updated %s⇢ ", GREY);
	print_window(RESULT, window, true);
	print_result_bot(true);
}

static void	print_window(t_style style, t_window *window, bool new_line)
{
	if (!should_print(style))
		return ;
	fprintf(stderr, "[min %3u | med %3u | max %3u | size %3zu | treated %3zu]", window->min, window->median.median, window->max, window->size, window->treated_count);
	if (new_line)
		fprintf(stderr, "\n");
}
