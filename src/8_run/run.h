#ifndef RUN_H
# define RUN_H

# include "state.h"
# include "config.h"

typedef struct s_run
{
	t_state		state;
	t_config	config;
}	t_run;

bool	run_all(t_run *dst, const t_state *state, const t_configs *configs);
bool	run_run(t_run *dst, const t_state *state, const t_config *config);
bool	run_init(t_run *dst, const t_state *state, const t_config *config);
bool	run_dup(t_run *dst, const t_run *src);
void	run_free(t_run *run);

#endif
