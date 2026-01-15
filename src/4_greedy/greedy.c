#include <cost.h>
#include "libft.h"
#include "stack.h"

typedef struct s_insert
{
	size_t			from_index;
	size_t			target_index;
	t_total_cost	cost;
}	t_insert;

static t_insert	get_next_insert(t_stack *from, t_stack *to);
static bool		add_all_moves(t_buff *move_list, t_insert *insertion);
static bool		add_move(t_buff *move_list, t_move move, size_t count);
static bool		exec_moves(t_stack *a, t_stack *b, t_insert *insertion);

# include <stdio.h>
bool	greedy(t_stack *a, t_stack *b, t_buff *move_list)
{
	t_insert	next_insertion;

	while (b->len > 0)
	{
		next_insertion = get_next_insert(b, a);
		add_all_moves(move_list, &next_insertion);
		exec_moves(a, b, &next_insertion);
		stack_print(a, b);
		printf("\n");
	}
	return (true);
}

# include <stdio.h>
static t_insert	get_next_insert(t_stack *from, t_stack *to)
{
	size_t		i;
	bool		best_is_set;
	t_insert	best;
	t_insert	current;
	uint		current_value;

	ft_bzero(&best, sizeof best);
	best_is_set = false;
	i = 0;
	while (i < from->len)
	{
		ft_bzero(&current, sizeof current);
		current.from_index = i;
		current_value = stack_get_value(from, i);
		current.target_index = stack_get_target_index(to, current_value);
		current.cost = get_best_cost(to, current.target_index, from, i);
		if (!best_is_set || current.cost.total < best.cost.total)
		{
			best = current;
			best_is_set = true;
		}
		i++;
	}
	return (best);
}

static bool	exec_moves(t_stack *a, t_stack *b, t_insert *insertion)
{
	while (insertion->cost.rr--)
		stack_rotate(a, b, BOTH, false);
	while (insertion->cost.ra--)
		stack_rotate(a, b, A, false);
	while (insertion->cost.rb--)
		stack_rotate(a, b, B, false);
	while (insertion->cost.rrr--)
		stack_rotate(a, b, BOTH, true);
	while (insertion->cost.rra--)
		stack_rotate(a, b, A, true);
	while (insertion->cost.rrb--)
		stack_rotate(a, b, B, true);
	if (stack_push(b, a, A) == ERROR)
		return (false);
	return (true);
}

static bool	add_all_moves(t_buff *move_list, t_insert *insertion)
{
	if (!add_move(move_list, RR, insertion->cost.rr))
		return (false);
	if (!add_move(move_list, RRR, insertion->cost.rrr))
		return (false);
	if (!add_move(move_list, RA, insertion->cost.ra))
		return (false);
	if (!add_move(move_list, RB, insertion->cost.rb))
		return (false);
	if (!add_move(move_list, RRA, insertion->cost.rra))
		return (false);
	if (!add_move(move_list, RRB, insertion->cost.rrb))
		return (false);
	if (!add_move(move_list, PA, 1))
		return (false);
	return (true);
}

static bool	add_move(t_buff *move_list, t_move move, size_t count)
{
	char	enum_as_char;

	if (move == NO_OP)
		return (true);
	enum_as_char = (char)move;
	while (count > 0)
	{
		if (!buff_append(move_list, &enum_as_char, 1))
			return (false);
		count--;
	}
	return (true);
}
