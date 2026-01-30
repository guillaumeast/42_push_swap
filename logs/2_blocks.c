#include "logs.h"
#include "logs_priv.h"
#include <stdio.h>

void	print_as(t_style style, bool padding, bool new_line, const char *fmt, ...)
{
	va_list	args;

	if (!should_print(style))
		return ;
	if (padding)
	{
		if (style == RESULT && should_print_as(style) == LOG)
			_print_padding(DEFAULT_PAD, PADDING_LEN_OF(DEPTH - 1));
		else
			_print_padding(DEFAULT_PAD, PADDING_LEN);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	if (new_line)
		fprintf(stderr, "\n");
}

void	print_link(long len, const char *color, bool new_line)
{
	if (len == 0)
		return ;
	else if (len == 1)
		fprintf(stderr, "%s\\%s", color, NC);
	else if (len == -1)
		fprintf(stderr, "%s/%s", color, NC);
	else if (len > 0)
	{
		fprintf(stderr, "%s╰", color);
		_print_padding("─", len - 2);
		fprintf(stderr, "╮%s", NC);
	}
	else if (len < 0)
	{
		len *= -1;
		fprintf(stderr, "%s╭", color);
		_print_padding("─", len - 2);
		fprintf(stderr, "╯%s", NC);
	}
	if (new_line)
		fprintf(stderr, "\n");
}

void	print_padding(t_style style, const char *pad, long padding_len)
{
	if (should_print(style))
		_print_padding(pad, padding_len);
}

void	_print_padding(const char *pad, long padding_len)
{
	char	res[TITLE_MAX_LEN];
	long	i;
	size_t	j;
	size_t	k;

	if (padding_len <= 0)
		return ;
	res[0] = '\0';
	i = 0;
	j = 0;
	while (i < padding_len && j < TITLE_MAX_LEN - 1)
	{
		k = 0;
		while (pad[k] && j < TITLE_MAX_LEN - 1)
			res[j++] = pad[k++];
		i++;
	}
	res[j] = '\0';
	fprintf(stderr, "%s", res);
}

void	print_array_u(t_style style, uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl)
{
	uint	current;
	size_t	i;

	if (!should_print(style))
		return ;
	fprintf(stderr, "%s[", array_color);
	i = 0;
	while (i < len)
	{
		current = array[i];
		if (current == value)
			fprintf(stderr, "%s%u%s", value_color, array[i], array_color);
		else
			fprintf(stderr, "%u", array[i]);
		if (i < len - 1)
			fprintf(stderr, " ");
		i++;
	}
	fprintf(stderr, "]%s", NC);
	if (nl)
		fprintf(stderr, "\n");
}

void	print_array_zu(t_style style, size_t *array, size_t len, const char *array_color, const char *value_color, size_t value, bool nl)
{
	size_t	current;
	size_t	i;

	if (!should_print(style))
		return ;
	fprintf(stderr, "%s[", array_color);
	i = 0;
	while (i < len)
	{
		current = array[i];
		if (current == value)
			fprintf(stderr, "%s%zu%s", value_color, array[i], array_color);
		else
			fprintf(stderr, "%zu", array[i]);
		if (i < len - 1)
			fprintf(stderr, " ");
		i++;
	}
	fprintf(stderr, "]%s", NC);
	if (nl)
		fprintf(stderr, "\n");
}

/* -------------------- OLD -------------------- */

void	log_debug(const char *func_name, size_t depth, const char *message, ...)
{
	va_list args;
	
	va_start(args, message);
	while (depth--)
		fprintf(stderr, "%s>", BOLD_YELLOW);
	fprintf(stderr, "%s> 🔦 %s()%s ", BOLD_YELLOW, func_name, NC);
	vfprintf(stderr, message, args);
	va_end(args);
}
