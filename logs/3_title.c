#define _GNU_SOURCE
#include "libft.h"
#include "logs.h"
#include "logs_priv.h"
#include <stdlib.h>
#include <stdio.h>

static void	_print_title_top(bool new_line);
static void	_print_title_mid(bool new_line, const char *fmt, va_list args);

void	print_title(const char *fmt, ...)
{
	va_list	args;

	g_depth.curr++;
	if (!should_print(TITLE))
		return ;
	_print_title_top(true);
	va_start(args, fmt);
	_print_title_mid(true, fmt, args);
	va_end(args);
}

void	print_title_top(bool new_line)
{
	g_depth.curr++;
	if (should_print(TITLE))
		_print_title_top(new_line);
}

void	print_title_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	_print_title_mid(new_line, fmt, args);
	va_end(args);
}

static void	_print_title_top(bool new_line)
{
	if (DEPTH < 0)
		return ;
	if (DEPTH == 0)
		fprintf(stderr, "%s│%s\n", TITLE_COLOR, NC);
	else if (DEPTH > 1)
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
	if (DEPTH > 0)
		print_link(PADDING_LEN_OF(1) + 1, TITLE_COLOR, new_line);
}

static void	_print_title_mid(bool new_line, const char *fmt, va_list args)
{
	int		len;
	int		i;
	char	*formatted;

	len = vasprintf(&formatted, fmt, args);
	if (len < 0)
		return ;
	i = 0;
	while (i < len)
	{
		formatted[i] = (char)ft_toupper(formatted[i]);
		i++;
	}
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⏺ %s%s", TITLE_COLOR, formatted, NC);
	free(formatted);
	if (new_line)
		fprintf(stderr, "\n");
}
