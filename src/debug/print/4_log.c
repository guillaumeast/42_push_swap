#include "print.h"
#include "print_priv.h"
#include <stdio.h>

void	print_log(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(true, true, fmt, args);
	va_end(args);
}

void	print_log_result(bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(RESULT))
		return ;
	va_start(args, fmt);
	_print_log_custom(false, new_line, fmt, args);
	va_end(args);
}

void	print_log_custom(bool indent, bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(indent, new_line, fmt, args);
	va_end(args);
}

void	_print_log_custom(bool indent, bool new_line, const char *fmt, va_list args)
{
	if (indent)
		_print_padding(DEFAULT_PAD, PADDING_LEN);
	vfprintf(stderr, fmt, args);
	if (new_line)
		fprintf(stderr, "\n");
}
