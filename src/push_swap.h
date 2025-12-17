#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct s_stack
{
	int		*values;
	size_t	count;
	size_t	cap;
}	t_stack;

typedef struct s_sort_data
{
	int		*array;
	int		*tmp;
}	t_sort_data;

/*---------- args.c ----------*/

bool	parse_args(char **argv, t_stack *a);

/*---------- stack.c ----------*/

bool	stack_init(t_stack *a, t_stack *b, size_t capacity);
bool	stack_convert_to_sorted_indexes(t_stack *a);
void	stack_free(t_stack *a, t_stack *b);

/*---------- sort.c ----------*/

bool	sort(int **array, size_t size);

#endif
