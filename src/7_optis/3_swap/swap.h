#ifndef SWAP_H
# define SWAP_H

# include "state.h"
# include "config.h"

bool	opti_swap_b(t_state *state, const t_config *config);
bool	opti_swap_lis(t_state *state, const t_config *config, uint value);

#endif
