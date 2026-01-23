#include "stack.h"
#include <stdio.h>

static int	get_idx_len(size_t max_size);
static void	print_line(t_stack *a, t_stack *b, size_t i, int len, int idx_len);
static void	print_sep(int max_value_len, int idx_len);
static int	get_max_len(t_stack *a, t_stack *b);
static int	get_value_len(uint nb);

void	stack_print_line(t_stack *stack)
{
	uint	value;
	size_t	i;

	fprintf(stderr, "[");
	i = 0;
	while (i < stack->len)
	{
		value = stack_get_value(stack, i);
		fprintf(stderr, "%u", value);
		if (stack->len - i > 1)
			fprintf(stderr, " ");
		i++;
	}
	fprintf(stderr, "]\n");
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
