#include "stack.h"
#include <stdio.h>

static void	print_sep(int max_value_len);
static int	get_max_len(t_stack *a, t_stack *b);
static int	get_value_len(int nb);

void	stack_print(t_stack *a, t_stack *b)
{
	size_t	i;
	size_t	idx_a;
	size_t	idx_b;
	int		max_value_len;

	max_value_len = get_max_len(a, b);
	print_sep(max_value_len);
	fprintf(stderr, "| %*s | %*s |\n", max_value_len, "A", max_value_len, "B");
	print_sep(max_value_len);
	i = 0;
	idx_a = a->offset;
	idx_b = b->offset;
	while (i < a->cap)
	{
		fprintf(stderr, "| %*i | %*i |\n", max_value_len, a->values[idx_a],
			max_value_len, b->values[idx_b]);
		idx_a = (idx_a + 1) % a->cap;
		idx_b = (idx_b + 1) % b->cap;
		i++;
	}
	print_sep(max_value_len);
	fprintf(stderr, "| %*zu | %*zu |\n", max_value_len, a->len,
		max_value_len, b->len);
	print_sep(max_value_len);
}

static void	print_sep(int max_value_len)
{
	size_t	sep_len;
	size_t	i;

	sep_len = 2 * (size_t)max_value_len + 7;
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
	while (i < a->cap)
	{
		len = get_value_len(a->values[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	i = 0;
	while (i < b->cap)
	{
		len = get_value_len(b->values[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

static int	get_value_len(int nb)
{
	int	value;
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
