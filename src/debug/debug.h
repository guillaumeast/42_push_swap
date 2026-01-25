#ifndef DEBUG_H
# define DEBUG_H

// TMP: remove before submit

# include "config.h"
# include "lis.h"
# include <stdio.h>

# define GREY "\033[0;90m"
# define BOLD_GREEN "\033[1;32m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define NC "\033[0m"

/* ---------- stack.c ---------- */

void	stack_print_line(const t_stack *stack, const t_stack *versus, const char *color);
void	stack_print(const t_stack *a, const t_stack *b);

/* ---------- config.c ---------- */

void	config_print_all(const t_configs *configs);
void	config_print(const t_config *config, size_t index, bool print_index);

/* ---------- lis.c ---------- */

void	lis_print(const t_lis *lis, size_t len);
void	print_bool_array(const bool *arr, const bool *versus, size_t len, const char *color);

/* ---------- LOGS ---------- */

void	log_debug(const char *func_name, size_t depth, const char *message, ...)
	__attribute__((format(printf, 3, 4)));

void	print_array_u(uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl);

#endif
