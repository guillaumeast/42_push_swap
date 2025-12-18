#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stddef.h>

typedef enum e_stack_choice
{
	A,
	B,
	BOTH
}	t_stack_choice;

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

/*---------- extract.c ----------*/

void	extract_from_a_to_b(t_stack *a, t_stack *b);

/*---------- push_swap.c ----------*/

void	push(t_stack *a, t_stack *b, t_stack_choice choice);
void	swap(t_stack *a, t_stack *b, t_stack_choice choice);

/*---------- rotate.c ----------*/

void	rotate(t_stack *a, t_stack *b, t_stack_choice choice);
void	rotate_reverse(t_stack *a, t_stack *b, t_stack_choice choice);

#endif
