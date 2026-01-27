#include "libft.h"
#include "print.h"
#include "print_priv.h"
#include <stdio.h>
#include <stdlib.h>

static void	_print_result_mid(bool new_line, const char *fmt, va_list args);
static void	_print_result_bot(bool new_line);

void	print_result(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(RESULT))
		return ;
	else if (should_print_as(RESULT) == LOG)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN);
		fprintf(stderr, "%s✔︎ ", GREEN);
		va_start(args, fmt);
		_print_log_custom(false, true, fmt, args);
		va_end(args);
		fprintf(stderr, "%s", NC);
	}
	else
	{
		va_start(args, fmt);
		_print_result_mid(true, fmt, args);
		va_end(args);
		_print_result_bot(true);
	}
	g_depth.curr--;
}

void	print_result_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(RESULT))
		return ;
	else if (should_print_as(RESULT) == LOG)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN);
		fprintf(stderr, "%s✔︎ ", GREEN);
		va_start(args, fmt);
		_print_log_custom(false, new_line, fmt, args);
		va_end(args);
		fprintf(stderr, "%s", NC);
	}
	else
	{
		va_start(args, fmt);
		_print_result_mid(new_line, fmt, args);
		va_end(args);
	}
}

void	print_result_bot(bool new_line)
{
	if (should_print(TITLE))
		_print_result_bot(new_line);
	g_depth.curr--;
}

static void	_print_result_mid(bool new_line, const char *fmt, va_list args)
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
	fprintf(stderr, "%s⏺ %s%s", RESULT_COLOR, formatted, NC);
	free(formatted);
	if (new_line)
		fprintf(stderr, "\n");
}

static void	_print_result_bot(bool new_line)
{
	if (DEPTH <= 0)
		return ;
	_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
	print_link(-(PADDING_LEN_OF(1)), RESULT_COLOR, new_line);
}
