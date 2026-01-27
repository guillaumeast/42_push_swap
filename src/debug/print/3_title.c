#include "libft.h"
#include "print.h"
#include "print_priv.h"
#include <stdio.h>

static void	_print_title_top(bool new_line, size_t len);
static void	_print_title_mid(bool new_line, char *title, size_t len);
static void	_print_title_bot(bool new_line, size_t len);

void	print_title(const char *fmt, ...)
{
	va_list	args;
	long	len;
	char	formatted[TITLE_MAX_LEN];

	g_depth.curr++;
	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	len = vsnprintf(formatted, TITLE_MAX_LEN, fmt, args);
	va_end(args);
	_print_title_top(true, (size_t)len);
	_print_title_mid(true, formatted, (size_t)len);
	_print_title_bot(true, (size_t)len);
}

void	print_title_top(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	buffer[TITLE_MAX_LEN];
	size_t	len;

	g_depth.curr++;
	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	vsnprintf(buffer, TITLE_MAX_LEN, fmt, args);
	va_end(args);
	len = str_len(buffer);
	_print_title_top(new_line,len);
}

void	print_title_mid(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	buffer[TITLE_MAX_LEN];
	size_t	len;

	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	vsnprintf(buffer, TITLE_MAX_LEN, fmt, args);
	va_end(args);
	len = str_len(buffer);
	_print_title_mid(new_line, buffer, len);
}

void	print_title_bot(bool new_line, const char *fmt, ...)
{
	va_list	args;
	char	buffer[TITLE_MAX_LEN];
	size_t	len;

	if (!should_print(TITLE))
		return ;
	va_start(args, fmt);
	vsnprintf(buffer, TITLE_MAX_LEN, fmt, args);
	va_end(args);
	len = str_len(buffer);
	_print_title_bot(new_line, len);
}

static void	_print_title_top(bool new_line, size_t len)
{
	if (DEPTH > 0)
	{
		_print_padding(DEFAULT_PAD, PADDING_LEN_OF((DEPTH - 1)));
		print_link((long)len + 4 + PADDING_LEN_OF(1), TITLE_COLOR, new_line);
	}
	else
		print_link((long)len + 4, TITLE_COLOR, new_line);
}

static void	_print_title_mid(bool new_line, char *title, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && title[i])
	{
		title[i] = (char)ft_toupper(title[i]);
		i++;
	}
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	fprintf(stderr, "%s⏺ %s │%s", TITLE_COLOR, title, NC);
	if (new_line)
		fprintf(stderr, "\n");
}

static void	_print_title_bot(bool new_line, size_t len)
{
	_print_padding(DEFAULT_PAD, PADDING_LEN);
	print_link(-((long)len + 4), TITLE_COLOR, new_line);
}
