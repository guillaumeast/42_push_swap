#include "logs.h"
#include "logs_priv.h"

void	print_start(size_t layers_count, const char *optional_title)
{
	long	future_min;
	long	future_display_depth;

	if (g_depth.curr < 0)
		g_depth.curr = 0;
	if (g_depth.min <= 0 || g_depth.min > g_depth.curr)
		future_min = g_depth.curr;
	else
		future_min = g_depth.min;
	future_display_depth = DEPTH_OF(g_depth.curr, future_min);
	if (DEPTH > 0 && DEPTH != future_display_depth)
	{
		if (future_display_depth <= 0)
			print_link(-PADDING_LEN, GREY, true);
		else
		{
			_print_padding(DEFAULT_PAD, PADDING_LEN);
			print_link(PADDING_LEN_OF((future_display_depth - DEPTH)), GREY, true);
		}
	}
	g_depth.min = future_min;
	g_depth.max = g_depth.curr + ((long)layers_count - 1);
	if (optional_title)
		print_log("%s⌽%s LOGS STARTED ⇢ %s%s\n", GREEN, BOLD_YELLOW, optional_title, NC);
	else
		print_log("%s⌽%s LOGS STARTED\n", GREEN, BOLD_YELLOW);
}

void	print_reset(void)
{
	long	future_display_depth;

	print_log("%s⍟ LOGS RESETED%s\n", BOLD_YELLOW, NC);
	if (g_depth.curr >= DEFAULT_DEPTH_MIN && g_depth.curr <= DEFAULT_DEPTH_MAX)
		return ;
	future_display_depth = DEPTH_OF(g_depth.curr, DEFAULT_DEPTH_MIN);
	if (future_display_depth <= 0)
		print_link(-PADDING_LEN, GREY, true);
	else if (future_display_depth > 0)
		print_link(PADDING_LEN_OF((future_display_depth - DEPTH)), GREY, true);
	g_depth.min = DEFAULT_DEPTH_MIN;
	g_depth.max = DEFAULT_DEPTH_MAX;
}

void	print_stop(void)
{
	print_log("%s⍉%s LOGS STOPPED%s\n", BOLD_RED, YELLOW, NC);
	if (DEPTH > 0)
		print_link(-(PADDING_LEN + 1), GREY, true);
	g_depth.min = -1;
	g_depth.max = -1;
}
