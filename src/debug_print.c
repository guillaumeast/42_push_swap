#include "push_swap.h"
#include <stdio.h>

static void	print_sep(int max_value_len);
static int	get_max_len(t_stack *a, t_stack *b);
static int	get_value_len(int nb);

void debug_print(t_stack *a, t_stack *b)
{
	size_t	i;
	size_t	max_stack_count;
	int		max_value_len;

	max_value_len = get_max_len(a, b);
	max_stack_count = a->count;
	if (b->count > a->count)
		max_stack_count = b->count;
	print_sep(max_value_len);
	fprintf(stderr, "| %*s | %*s |\n", max_value_len, "A", max_value_len, "B");
	print_sep(max_value_len);
	i = 0;
	while (i < max_stack_count)
	{
		if (i < a->count && i < b->count)
			fprintf(stderr, "| %*i | %*i |\n", max_value_len, a->values[i], max_value_len, b->values[i]);
		else if (i < a->count)
			fprintf(stderr, "| %*i | %*s |\n", max_value_len, a->values[i], max_value_len, "");
		else
			fprintf(stderr, "| %*s | %*i |\n", max_value_len, "", max_value_len, b->values[i]);
		i++;
	}
	print_sep(max_value_len);
	fprintf(stderr, "| %*zu | %*zu |\n", max_value_len, a->count, max_value_len, b->count);
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
	while (i < a->count)
	{
		len = get_value_len(a->values[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	i = 0;
	while (i < b->count)
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
