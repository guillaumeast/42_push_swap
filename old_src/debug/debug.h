#ifndef DEBUG_H
# define DEBUG_H

# include "config.h"
# include "lis.h"
# include <stdio.h>

// DEPRECATED (in print/utils.c)
void	log_debug(const char *func_name, size_t depth, const char *message, ...)	__attribute__((format(printf, 3, 4)));

/* ---------- stack.c ---------- */

void	stack_print_line(const t_stack *stack, const t_stack *versus, const char *color);
void	stack_print(const t_stack *a, const t_stack *b);

/* ---------- config.c ---------- */

void	config_print_all(const t_configs *configs);
void	config_print(const t_config *config, size_t index, bool print_index);

void	config_print_raw(const uint *configs, size_t count, const char *color, const char *item_color, bool nl);
void	config_print_algo_1(const uint *configs, size_t count, const char *color, const char *item_color, bool nl);
void	config_print_algo_2(const uint *configs, size_t count, const char *color, const char *item_color, bool nl);
void	config_print_optis(const uint *configs, size_t count, const char *color, const char *item_color, bool nl);

/* ---------- lis.c ---------- */

void	lis_print(const t_lis *lis, size_t len);
void	print_bool_array(const bool *arr, const bool *versus, size_t len, const char *color);

/* ---------- opti_moves.c ---------- */

bool	test_opti_moves(void);
void	print_opti_moves(t_buff *moves, size_t start, size_t end, const char *color, const char *highlight, bool nl);

#endif
