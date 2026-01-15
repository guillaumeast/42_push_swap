#ifndef ARGS_PRIV_H
# define ARGS_PRIV_H

# include <stdbool.h>
# include <sys/types.h>

/* --- convert.c --- */

bool	convert_arg(char *arg, int *args, size_t *args_count);

/* --- normalize.c --- */

uint	*normalize(int *array, size_t size);

#endif
