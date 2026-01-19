#ifndef SWAP_H
# define SWAP_H

# include "state.h"
# include "config.h"
# include "lis.h"

bool	opti_swap_b(t_state *state, t_config *config);
bool	opti_swap_lis(t_state *state, t_lis *lis, uint current_value);

#endif
