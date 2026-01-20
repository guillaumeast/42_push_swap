#ifndef DEBUG_H
# define DEBUG_H

// TMP: remove before submit

# include "config.h"
# include "lis.h"
# include <stdio.h>

/* ---------- stack.c ---------- */

void	stack_print(t_stack *a, t_stack *b);

/* ---------- config.c ---------- */

void	config_print_all(t_config_list *configs);
void	config_print(t_config *config, size_t index, bool print_index);

/* ---------- lis.c ---------- */

void	lis_print(t_state *state, t_lis *lis);

#endif
