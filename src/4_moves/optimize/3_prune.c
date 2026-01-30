#include "libft.h"
#include "optimize_priv.h"

static void	prune_pattern(t_buff *moves, size_t *index, t_pattern *pat);
static void	prune_doublon(t_buff *moves, size_t *index, t_move move);
static void	convert_pattern(t_buff *dst, t_pattern *pat, size_t i);

void	prune_all(t_buff *moves)
{
	t_pattern	pattern;
	size_t		last_i;
	size_t		i;

	i = 0;
	last_i = 0;
	while (i < moves->len)
	{
		prune_doublon(moves, &i, SA);
		prune_doublon(moves, &i, SB);
		prune_doublon(moves, &i, SS);
		pattern_init(&pattern, RA, RRA, NO_OP);
		prune_pattern(moves, &i, &pattern);
		pattern_init(&pattern, RB, RRB, NO_OP);
		prune_pattern(moves, &i, &pattern);
		pattern_init(&pattern, RR, RRR, NO_OP);
		prune_pattern(moves, &i, &pattern);
		pattern_init(&pattern, PA, PB, NO_OP);
		prune_pattern(moves, &i, &pattern);
		if (i == last_i)
			i++;
		last_i = i;
	}
}

static void	prune_pattern(t_buff *moves, size_t *index, t_pattern *pat)
{
	t_move	curr;
	size_t	i;

	i = *index;
	set_move(&curr, moves, (long)i);
	while (i < moves->len && (curr == pat->a_move || curr == pat->b_move || curr == pat->cumul_move))
	{
		if (curr == pat->a_move)
			pat->a_count++;
		if (curr == pat->b_move)
			pat->b_count++;
		if (curr == pat->cumul_move)
			pat->cumul_count++;
		i++;
		set_move(&curr, moves, (long)i);
	}
	if (pat->a_count > 0 && pat->b_count > 0)
	{
		pat->cumul_new = (size_t)min((long)pat->a_count, (long)pat->b_count) * 2;
		pat->a_count -= pat->cumul_new / 2;
		pat->b_count -= pat->cumul_new / 2;
		convert_pattern(moves, pat, *index);
	}
	*index = i;
}

static void	prune_doublon(t_buff *moves, size_t *index, t_move move)
{
	t_pattern	pattern;
	t_move		curr;
	size_t		i;

	pattern_init(&pattern, move, move, NO_OP);
	i = *index;
	set_move(&curr, moves, (long)i);
	while (i < moves->len && (curr == move || curr == NO_OP))
	{
		if (curr == move)
			pattern.a_count++;
		if (curr == NO_OP)
			pattern.cumul_count++;
		i++;
		set_move(&curr, moves, (long)i);
	}
	if (pattern.a_count > 1)
	{
		pattern.cumul_new = pattern.a_count - (pattern.a_count % 2);
		pattern.a_count = pattern.a_count % 2;
		convert_pattern(moves, &pattern, *index);
	}
	*index = i;
}


static void	convert_pattern(t_buff *dst, t_pattern *pat, size_t i)
{
	while (pat->a_count--)
		dst->data[i++] = (char)pat->a_move;
	while (pat->b_count--)
		dst->data[i++] = (char)pat->b_move;
	while (pat->cumul_new--)
		dst->data[i++] = (char)NO_OP;
	while (pat->cumul_count--)
		dst->data[i++] = (char)pat->cumul_move;
}
