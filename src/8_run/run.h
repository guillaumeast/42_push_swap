#ifndef RUN_H
# define RUN_H

# include "state.h"
# include "config.h"

typedef struct s_run
{
	t_state		state;
	t_config	config;
}	t_run;

void	run_init(t_run *dst, t_state *state, t_config *config);
bool	run_dup(t_run *dst, const t_run *src);
bool	run_run(t_run *run);
void	run_free(t_run *run);

#endif
