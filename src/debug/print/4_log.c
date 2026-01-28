#include "print.h"
#include "print_priv.h"
#include <stdio.h>

void	print_log(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(NONE, true, false, fmt, args);
	va_end(args);
}

void	print_info(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(INFO, true, false, fmt, args);
	va_end(args);
}

void	print_warn(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(WARN, true, false, fmt, args);
	va_end(args);
}

void	print_pass(const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(PASS, true, false, fmt, args);
	va_end(args);
}

void	print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(LOG))
		return ;
	va_start(args, fmt);
	_print_log_custom(format, indent, new_line, fmt, args);
	va_end(args);
}

void	_print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, va_list args)
{
	if (indent)
		_print_padding(DEFAULT_PAD, PADDING_LEN);
	if (format == INFO)
		fprintf(stderr, "%s⏺ ", GREY);
	else if (format == WARN)
		fprintf(stderr, "%s⚑ %s", YELLOW, GREY);
	else if (format == PASS)
		fprintf(stderr, "%s✔ %s", GREEN, GREY);
	vfprintf(stderr, fmt, args);
	if (new_line)
		fprintf(stderr, "%s\n", NC);
}
