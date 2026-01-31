#ifndef LOGS_H
# define LOGS_H

# include <stdbool.h>
# include <sys/types.h>

/* ---------- TYPES ---------- */

typedef enum e_style
{
	TITLE,
	LOG,
	RESULT,
	HIDDEN,
	FORCED
}	t_style;

typedef enum e_format
{
	NONE,
	INFO,
	WARN,
	PASS
}	t_format;

typedef struct s_depth
{
	long	curr;
	long	min;
	long	max;
}	t_depth;

extern t_depth	g_depth;

/* ---------- COLORS ---------- */

# define GREY "\033[0;90m"
# define BOLD_GREY "\033[1;90m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define BLUE "\033[0;34m"
# define BOLD_BLUE "\033[1;34m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define NC "\033[0m"

/* ---------- SETTINGS ---------- */

# define DEFAULT_DEPTH_CURR	-1
# define DEFAULT_DEPTH_MIN	-1
# define DEFAULT_DEPTH_MAX	-1
# define DEFAULT_PAD		" "
# define PADDING_SIZE		6
# define TITLE_COLOR		BOLD_BLUE
# define RESULT_COLOR		BOLD_GREEN

/* ---------- GETTERS ---------- */

# define DEPTH_OF(current, min)	(min < 0 ? -2 : current - min)
# define DEPTH					DEPTH_OF(g_depth.curr, g_depth.min)
# define PADDING_LEN_OF(depth)	(depth * PADDING_SIZE)
# define PADDING_LEN			PADDING_LEN_OF(DEPTH)
# define LINK_LEN_OF(depth)		(PADDING_LEN_OF(depth) + 1)

/* ---------- DEBUG ---------- */

#include <stdio.h>
inline void	print_depth(void)
{
	fprintf(stderr, "DEPTH = %ld | curr = %ld | min = %ld | max = %ld\n", DEPTH, g_depth.curr, g_depth.min, g_depth.max);
}

/* ---------- check.c ---------- */

bool	should_print(t_style style);
t_style	should_print_as(t_style style);

/* ---------- life_cycle.c ---------- */

void	print_start(size_t layers_count, const char *optional_title);
void	print_reset(void);
void	print_stop(void);

/* ---------- blocks.c ---------- */

void	print_as(t_style style, bool padding, bool new_line, const char *fmt, ...)			__attribute__((format(printf, 4, 5)));
void	print_link(long len, const char *color, bool new_line);
void	print_padding(t_style style, const char *pad, long padding_len);
void	print_array_u(t_style style, uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl);
void	print_array_zu(t_style style, size_t *array, size_t len, const char *array_color, const char *value_color, size_t value, bool nl);

/* ---------- error.c ---------- */

void	print_error(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));

/* ---------- title.c ---------- */

void	print_title(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_title_top(bool new_line);
void	print_title_mid(bool new_line, const char *fmt, ...)								__attribute__((format(printf, 2, 3)));

/* ---------- log.c ---------- */

void	print_log(const char *fmt, ...)														__attribute__((format(printf, 1, 2)));
void	print_info(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_warn(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_pass(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_log_custom(t_format format, bool indent, bool new_line, const char *fmt, ...) __attribute__((format(printf, 4, 5)));

/* ---------- result.c ---------- */

void	print_result(const char *fmt, ...)													__attribute__((format(printf, 1, 2)));
void	print_result_mid(bool new_line, const char *fmt, ...)								__attribute__((format(printf, 2, 3)));
void	print_result_bot(bool new_line);

#endif
