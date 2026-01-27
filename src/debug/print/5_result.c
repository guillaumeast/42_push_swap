#include "libft.h"
#include "print.h"
#include "print_priv.h"
#include <stdio.h>

static void	_print_result_top(bool new_line, size_t len);
static void	_print_result_mid(bool new_line, char *result, size_t len);
static void	_print_result_bot(bool new_line, size_t len);

void	print_result(const char *fmt, ...)
{
	va_list	args;
	long	len;
	char	formatted[TITLE_MAX_LEN];

	if (should_print_as(RESULT) == LOG)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
		snprintf(formatted, TITLE_MAX_LEN, "%s✔︎ ", GREEN);
		_print_log_custom(false, false, formatted, NULL);
		va_start(args, fmt);
		_print_log_custom(false, true, fmt, args);
		va_end(args);
	}
	else if (should_print(RESULT))
	{
		va_start(args, fmt);
		len = vsnprintf(formatted, TITLE_MAX_LEN, fmt, args);
		va_end(args);
		_print_result_top(true, (size_t)len);
		_print_result_mid(true, formatted, (size_t)len);
		_print_result_bot(true, (size_t)len);
	}
	g_depth.curr--;
}

void	print_result_top(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	formatted[TITLE_MAX_LEN];
	size_t	len;

	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	vsnprintf(formatted, TITLE_MAX_LEN, fmt, args);
	va_end(args);
	len = str_len(formatted);
	_print_result_top(new_line, len);
}

void	print_result_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	formatted[TITLE_MAX_LEN];
	size_t	len;

	if (!should_print(RESULT))
		return ;
	else if (!should_print(TITLE))
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
		snprintf(formatted, TITLE_MAX_LEN, "%s✔︎ ", GREEN);
		_print_log_custom(false, false, formatted, NULL);
		va_start(args, fmt);
		_print_log_custom(false, new_line, fmt, args);
		va_end(args);
	}
	else
	{
		va_start(args, fmt);
		vsnprintf(formatted, TITLE_MAX_LEN, fmt, args);
		va_end(args);
		len = str_len(formatted);
		_print_result_mid(new_line, formatted,len);
	}
}

void	print_result_bot(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	formatted[TITLE_MAX_LEN];
	size_t	len;

	if (should_print(TITLE))
	{
		va_start(args, fmt);
		vsnprintf(formatted, TITLE_MAX_LEN, fmt, args);
		va_end(args);
		len = str_len(formatted);
		_print_result_bot(new_line, len);
	}
	g_depth.curr--;
}

static void	_print_result_top(bool new_line, size_t len)
{
	print_link((long)len + 4, RESULT_COLOR, new_line);
}

static void	_print_result_mid(bool new_line, char *result, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		result[i] = (char)ft_toupper(result[i]);
		i++;
	}
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s✔︎ %s │%s", RESULT_COLOR, result, NC);
	if (new_line)
		fprintf(stderr, "\n");
}

static void	_print_result_bot(bool new_line, size_t len)
{
	if (DEPTH > 0)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
		print_link(-((long)len + 4 + PADDING_LEN_OF(1)), RESULT_COLOR, new_line);
	}
	print_link(-((long)len + 4), RESULT_COLOR, new_line);
}
