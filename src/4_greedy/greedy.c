#include "libft.h"
#include "stack.h"

typedef struct s_insertion
{
	int		from_index;
	int		target_index;
	size_t	ra;
	size_t	rra;
	size_t	rb;
	size_t	rrb;
	size_t	rr;
	size_t	rrr;
	size_t	total_cost;
}	t_insertion;

static t_insertion	get_next_insertion(t_stack *from, t_stack *to);
static void			compute_cost(t_insertion *i, size_t from_len, size_t to_len);
static bool			add_moves_all(t_buff *move_list, t_insertion *insertion);
static bool			add_move(t_buff *move_list, t_move move, size_t count);

bool	greedy_get_moves(t_stack *from, t_stack *to, t_buff *move_list)
{
	t_insertion	next_insertion;

	while (from->len > 0)
	{
		next_insertion = get_next_insertion(from, to);
		if (!add_moves_all(move_list, &next_insertion))
			return (false);
		// TODO: simulate moves
	}
	return (true);
}

static t_insertion	get_next_insertion(t_stack *from, t_stack *to)
{
	size_t		i;
	t_insertion	best;
	t_insertion	current;
	int			current_value;

	ft_bzero(&best, sizeof best);
	best.from_index = -1;
	i = 0;
	while (i < from->len)
	{
		ft_bzero(&current, sizeof current);
		current.from_index = (int)i;
		current_value = stack_get_value(from, i);
		current.target_index = stack_get_target_index(to, current_value);
		compute_cost(&current, from->len, to->len);
		if (best.from_index == -1 || current.total_cost < best.total_cost)
			best = current;
		i++;
	}
}

static void	compute_cost(t_insertion *i, size_t from_len, size_t to_len)
{
	if (i->target_index <= (int)to_len / 2)
		i->ra = (size_t)i->target_index;
	else
		i->rra = to_len - (size_t)i->target_index;
	if (i->from_index <= (int)from_len / 2)
		i->rb = (size_t)i->from_index;
	else
		i->rrb = from_len - (size_t)i->from_index;
	i->rr = (size_t)ft_min((int)i->ra, (int)i->rb);
	i->rrr = (size_t)ft_min((int)i->rra, (int)i->rrb);
	i->ra = i->ra - i->rr;
	i->rb = i->rb - i->rr;
	i->rra = i->rra - i->rrr;
	i->rrb = i->rrb - i->rrr;
	i->total_cost = i->ra + i->rb + i->rr + i->rra + i->rrb + i->rrr;
}

static bool	add_moves_all(t_buff *move_list, t_insertion *insertion)
{
	if (!add_move(move_list, RR, insertion->rr))
		return (false);
	if (!add_move(move_list, RRR, insertion->rrr))
		return (false);
	if (!add_move(move_list, RA, insertion->ra))
		return (false);
	if (!add_move(move_list, RB, insertion->rb))
		return (false);
	if (!add_move(move_list, RRA, insertion->rra))
		return (false);
	if (!add_move(move_list, RRB, insertion->rrb))
		return (false);
	if (!add_move(move_list, PA, 1))
		return (false);
	return (true);
}

// TODO: belek à l'overhead du t_buff
static bool	add_move(t_buff *move_list, t_move move, size_t count)
{
	char	enum_as_char;

	enum_as_char = (char)move;
	while (count > 0)
	{
		if (!buff_append(move_list, &enum_as_char, 1))
			return (false);
		count--;
	}
	return (true);
}

// TODO: update buff module to accept void * instead of char * (and update doc)
