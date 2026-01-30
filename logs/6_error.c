#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>

static void	print_here(const char *fmt, va_list args);
static void print_ahead(const char *fmt, va_list args);

void	print_error(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	if (g_depth.max >= 0 && g_depth.max < g_depth.curr)
		print_ahead(fmt, args);
	else
		print_here(fmt, args);
	va_end(args);
}

static void	print_here(const char *fmt, va_list args)
{
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⚑ ERROR AT DEPTH %ld ⇢ %s", BOLD_RED, g_depth.curr, NC);
	vfprintf(stderr, fmt, args);
}

static void print_ahead(const char *fmt, va_list args)
{
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((g_depth.max - g_depth.min)));
	print_link(LINK_LEN_OF(1), RED, true);
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((g_depth.max - g_depth.min + 1)));
	fprintf(stderr, "%s⚑ ERROR AT DEPTH %ld ⇢ %s", BOLD_RED, g_depth.curr, NC);
	vfprintf(stderr, fmt, args);
	print_link(-LINK_LEN_OF(1), RED, false);
}
