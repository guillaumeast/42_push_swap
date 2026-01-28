#include "libft.h"
#include "opti_moves_priv.h"
# include "debug.h"
# include <print.h>	// TMP: remove before submit

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
		// fprintf(stderr, "🪄  %s%3zu%s (%s%i%s) a_count = %3zu | b_count = %3zu | cumul_count = %3zu%s\n", YELLOW, *index, GREY, YELLOW, curr, GREY, pat->a_count, pat->b_count, pat->cumul_count, NC);	// TODO: tmp debug
		set_move(&curr, moves, (long)i);
	}
	if (pat->a_count > 0 && pat->b_count > 0)
	{
		pat->cumul_new = (size_t)min((long)pat->a_count, (long)pat->b_count) * 2;
		pat->a_count -= pat->cumul_new / 2;
		pat->b_count -= pat->cumul_new / 2;
		// fprintf(stderr, "%s✗ pruned %4zu%s => ", GREEN, pat->cumul_new, GREY);
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
		// fprintf(stderr, "🪄  %s%3zu%s (%s%i%s) a_count = %3zu | b_count = %3zu | cumul_count = %3zu%s\n", YELLOW, *index, GREY, YELLOW, curr, GREY, pat->a_count, pat->b_count, pat->cumul_count, NC);	// TODO: tmp debug
		set_move(&curr, moves, (long)i);
	}
	if (pattern.a_count > 1)
	{
		pattern.cumul_new = pattern.a_count - (pattern.a_count % 2);
		pattern.a_count = pattern.a_count % 2;
		fprintf(stderr, "%s✗ pruned %4zu%s => ", GREEN, pattern.cumul_new, GREY);
		convert_pattern(moves, &pattern, *index);
	}
	*index = i;
}


static void	convert_pattern(t_buff *dst, t_pattern *pat, size_t i)
{
	// size_t	start_index;
	// size_t	end_index;

	// start_index = i;
	// fprintf(stderr, "convert_pattern() pat->a_count = %ld | pat->b_count = %ld | pat->cumul_new = %zu\n", pat->a_count, pat->b_count, pat->cumul_new);
	while (pat->a_count--)
		dst->data[i++] = (char)pat->a_move;
	while (pat->b_count--)
		dst->data[i++] = (char)pat->b_move;
	while (pat->cumul_new--)
		dst->data[i++] = (char)NO_OP;
	// end_index = i;
	while (pat->cumul_count--)
		dst->data[i++] = (char)pat->cumul_move;
	// print_opti_moves(dst, start_index, end_index - 1, GREY, YELLOW, true);
}
