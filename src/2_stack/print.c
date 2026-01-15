#include "stack.h"
#include <stdio.h>

static void	print_line(t_stack *a, t_stack *b, size_t i, int len, int idx_len);
static void	print_sep(int max_value_len, int idx_len);
static int	get_max_len(t_stack *a, t_stack *b);
static int	get_value_len(uint nb);

static int	get_idx_len(size_t max_size)
{
	int	len;

	len = 1;
	while (max_size >= 10)
	{
		len++;
		max_size /= 10;
	}
	return (len);
}

void	stack_print(t_stack *a, t_stack *b)
{
	size_t	i;
	size_t	max_size;
	int		max_value_len;
	int		idx_len;

	max_value_len = get_max_len(a, b);
	if (max_value_len < 3)
		max_value_len = 3;
	max_size = a->len;
	if (b->len > max_size)
		max_size = b->len;
	idx_len = get_idx_len(max_size);
	if (idx_len < 3)
		idx_len = 3;
	print_sep(max_value_len, idx_len);
	fprintf(stderr, "| %*s | %*s | %*s || %*s | %*s | %*s |\n",
		idx_len, "idx", max_value_len, "A", max_value_len, "B",
		idx_len, "idx", max_value_len, "A", max_value_len, "B");
	fprintf(stderr, "| %*s | %*s | %*s || %*s | %*s | %*s |\n",
		idx_len, "mem", max_value_len, "mem", max_value_len, "mem",
		idx_len, "log", max_value_len, "log", max_value_len, "log");
	print_sep(max_value_len, idx_len);
	i = 0;
	while (i < max_size)
	{
		print_line(a, b, i, max_value_len, idx_len);
		i++;
	}
	print_sep(max_value_len, idx_len);
	fprintf(stderr, "| %*s | %*zu | %*zu || %*s | %*zu | %*zu |\n",
		idx_len, "len", max_value_len, a->len, max_value_len, b->len,
		idx_len, "off", max_value_len, a->offset, max_value_len, b->offset);
	print_sep(max_value_len, idx_len);
}

static void	print_line(t_stack *a, t_stack *b, size_t i, int len, int idx_len)
{
	char	a_mem[32];
	char	b_mem[32];
	char	a_log[32];
	char	b_log[32];

	a_mem[0] = '\0';
	b_mem[0] = '\0';
	a_log[0] = '\0';
	b_log[0] = '\0';
	if (i < a->len)
	{
		snprintf(a_mem, sizeof(a_mem), "%u", a->data[i]);
		snprintf(a_log, sizeof(a_log), "%u", stack_get_value(a, i));
	}
	if (i < b->len)
	{
		snprintf(b_mem, sizeof(b_mem), "%u", b->data[i]);
		snprintf(b_log, sizeof(b_log), "%u", stack_get_value(b, i));
	}
	fprintf(stderr, "| %*zu | %*s | %*s || %*zu | %*s | %*s |\n",
		idx_len, i, len, a_mem, len, b_mem,
		idx_len, i, len, a_log, len, b_log);
}

static void	print_sep(int max_value_len, int idx_len)
{
	size_t	sep_len;
	size_t	i;

	sep_len = 2 * ((size_t)idx_len + 2 * (size_t)max_value_len + 10);
	i = 0;
	while (i < sep_len)
	{
		fprintf(stderr, "-");
		i++;
	}
	fprintf(stderr, "\n");
}

static int	get_max_len(t_stack *a, t_stack *b)
{
	size_t	i;
	int		len;
	int		max_len;

	i = 0;
	max_len = 0;
	while (i < a->len)
	{
		len = get_value_len(stack_get_value(a, i));
		if (len > max_len)
			max_len = len;
		i++;
	}
	i = 0;
	while (i < b->len)
	{
		len = get_value_len(stack_get_value(b, i));
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

static int	get_value_len(uint nb)
{
	uint	value;
	int	len;

	value = nb;
	len = 1;
	if (value < 0)
	{
		len++;
		value = -value;
	}
	while (value >= 10)
	{
		len++;
		value /= 10;
	}
	return (len);
}

// TODO: tmp debug
#include "libft.h"
void	moves_print(t_buff *move_list)
{
	size_t	printed_bytes;
	t_move	move;

	ft_printf("MOVES:\n");
	printed_bytes = 0;
	while (printed_bytes < move_list->len)
	{
		move = (t_move)move_list->data[printed_bytes++];
		if (move == RR)
			ft_printf("RR\n");
		else if (move == RRR)
			ft_printf("RRR\n");
		else if (move == RA)
			ft_printf("RA\n");
		else if (move == RB)
			ft_printf("RB\n");
		else if (move == RRA)
			ft_printf("RRA\n");
		else if (move == RRB)
			ft_printf("RRB\n");
		else if (move == SS)
			ft_printf("SS\n");
		else if (move == SA)
			ft_printf("SA\n");
		else if (move == SB)
			ft_printf("SB\n");
		else if (move == PA)
			ft_printf("PA\n");
		else if (move == PB)
			ft_printf("PB\n");
		else if (move == NO_OP)
			ft_printf("PB\n");
		else
			ft_printf("???\n");
	}
}
