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

void	stack_print(t_stack *a, t_stack *b);

/* ---------- config.c ---------- */

void	config_print_all(t_config_list *configs);
void	config_print(t_config *config, size_t index, bool print_index);

/* ---------- lis.c ---------- */

void	lis_print(t_lis *lis, size_t len);
void	print_bool_array(bool *arr, size_t len);

/* ---------- LOGS ---------- */

void	log_debug(const char *func_name, size_t depth, const char *message, ...)
	__attribute__((format(printf, 3, 4)));

#endif
