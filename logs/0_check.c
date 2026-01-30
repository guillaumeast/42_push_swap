#include "logs.h"

t_depth	g_depth = {DEFAULT_DEPTH_CURR, DEFAULT_DEPTH_MIN, DEFAULT_DEPTH_MAX};

bool	should_print(t_style style)
{
	return (should_print_as(style) != HIDDEN);
}

t_style	should_print_as(t_style style)
{
	if (style == FORCED)
		return (style);
	if (g_depth.min < 0 || g_depth.max < 0)
		return (HIDDEN);
	if (g_depth.curr >= g_depth.min && g_depth.curr <= g_depth.max)
		return (style);
	if (style == RESULT && g_depth.curr == g_depth.max + 1)
		return (LOG);
	return (HIDDEN);
}
