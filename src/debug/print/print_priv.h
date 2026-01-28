#ifndef PRINT_PRIV_H
# define PRINT_PRIV_H

# include "print.h"
# include <stdarg.h>

# define TITLE_MAX_LEN	128

void	_print_padding(const char *pad, long padding_len);
void	_print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, va_list args);

#endif
