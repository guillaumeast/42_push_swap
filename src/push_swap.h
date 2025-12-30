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

typedef struct s_tail
{
	size_t	start_index;
	int		*array;
	size_t	max_len;
	int		*pos;
	int		*prev;
}	t_tail;

typedef struct s_lis
{
	size_t	start_index;
	bool	*keep;
	size_t	keep_count;
	bool	*swap;
	size_t	swap_count;
	size_t	final_len;
}	t_lis;

/*----------------------------------------------------*/
// TODO: tmp DEBUG
#include <stdio.h>
int	g_move_count;
void	debug_print_move_count(void);
void	debug_print(t_stack *a, t_stack *b);
/*----------------------------------------------------*/

/*---------- args.c ----------*/

bool	parse_args(int argc, char **argv, t_stack *a, t_stack *b);

/*---------- stack.c ----------*/

bool	stack_init(t_stack *a, t_stack *b, size_t capacity);
bool	stack_convert_to_sorted_indexes(t_stack *a);
void	stack_free(t_stack *a, t_stack *b);

/*---------- sort.c ----------*/

bool	sort(int **array, size_t size);

/*----------------------------------------------------*/
// TODO: tmp depending on version
bool	step_1(t_stack *a, t_stack *b);
bool	step_2(t_stack *a, t_stack *b);

/*---------- tail.c ----------*/

t_tail	*tail_get(t_stack *stack, size_t start_index);
void	tail_free(t_tail **tail);

/*---------- lis.c ----------*/

t_lis	*lis_get_best(t_stack *stack);
void	lis_free(t_lis **lis);

/*----------------------------------------------------*/

/*---------- push_swap.c ----------*/

void	push(t_stack *a, t_stack *b, t_stack_choice choice);
void	swap(t_stack *a, t_stack *b, t_stack_choice choice);

/*---------- rotate.c ----------*/

void	rotate(t_stack *a, t_stack *b, t_stack_choice choice);
void	rotate_reverse(t_stack *a, t_stack *b, t_stack_choice choice);

/*---------- finish.c ----------*/

bool	is_sorted(t_stack *stack);
bool	finish(t_stack *a, t_stack *b);

#endif
