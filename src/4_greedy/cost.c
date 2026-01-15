#include "cost.h"
#include "libft.h"

typedef struct s_cost
{
	size_t	rotate;
	size_t	reverse;
}	t_cost;

typedef struct s_cost_choice
{
	t_cost	opti;
	t_cost	bad;
}	t_cost_choice;

// # include <stdio.h>
// static void	print_cost_choice(t_cost_choice *cost, const char *name)
// {
// 	printf("=> cost %s = [opti.r = %zu | opti.rr = %zu | bad.r = %zu | bad.rr = %zu]\n", 
// 		name, cost->opti.rotate, cost->opti.reverse, cost->bad.rotate, cost->bad.reverse);
// }

// static void	print_cost(t_total_cost *cost, const char *name)
// {
// 	printf("===> %s = [rr = %zu | ra = %zu | rb = %zu | rrr = %zu | rra = %zu | rrb = %zu | total = %zu]\n",
// 		name, cost->rr, cost->ra, cost->rb, cost->rrr, cost->rra, cost->rrb, cost->total);
// }

static void	get_cost(size_t stack_len, size_t index, t_cost_choice *cost);
static void	cost_add(t_cost *a, t_cost *b, t_total_cost *res);

t_total_cost	get_best_cost(t_stack *a, size_t i_a, t_stack *b, size_t i_b)
{
	t_cost_choice	a_cost;
	t_cost_choice	b_cost;
	t_total_cost	best;
	t_total_cost	current;

	// printf("==> [i_b = %zu | i_a = %zu]\n", i_b, i_a);
	get_cost(a->len, i_a, &a_cost);
	// print_cost_choice(&a_cost, "a_cost");
	get_cost(b->len, i_b, &b_cost);
	// print_cost_choice(&b_cost, "b_cost");
	cost_add(&a_cost.opti, &b_cost.opti, &best);
	// print_cost(&best, "opti + opti");
	cost_add(&a_cost.opti, &b_cost.bad, &current);
	// print_cost(&best, "opti + bad");
	if (current.total < best.total)
		best = current;
	cost_add(&a_cost.bad, &b_cost.opti, &current);
	// print_cost(&best, "bad + opti");
	if (current.total < best.total)
		return (current);
	return (best);
}

static void	get_cost(size_t stack_len, size_t index, t_cost_choice *cost)
{
	if (index <= stack_len / 2)
	{
		cost->opti.rotate = index;
		cost->opti.reverse = 0;
		cost->bad.rotate = 0;
		cost->bad.reverse = stack_len - index;
	}
	else
	{
		cost->opti.rotate = 0;
		cost->opti.reverse = stack_len - index;
		cost->bad.rotate = index;
		cost->bad.reverse = 0;
	}
}

static void	cost_add(t_cost *a, t_cost *b, t_total_cost *res)
{
	res->rr = (size_t)min((long)a->rotate, (long)b->rotate);
	res->rrr = (size_t)min((long)a->reverse, (long)b->reverse);
	res->ra = a->rotate - res->rr;
	res->rb = b->rotate - res->rr;
	res->rra = a->reverse - res->rrr;
	res->rrb = b->reverse - res->rrr;
	res->total = res->rr + res->rrr + res->ra + res->rb + res->rra + res->rrb;
}
