#include "libft.h"
#include "opti_moves_priv.h"
# include "debug.h"

static void	merge_pattern(t_buff *moves, size_t *index, t_pattern *pat);
static void	convert_pattern(t_buff *dst, t_pattern *pat, size_t i);

void	merge_all(t_buff *moves)
{
	t_pattern	pattern;
	size_t		last_i;
	size_t		i;

	i = 0;
	last_i = 0;
	while (i < moves->len)
	{
		pattern_init(&pattern, SA, SB, SS);
		merge_pattern(moves, &i, &pattern);
		pattern_init(&pattern, RA, RB, RR);
		merge_pattern(moves, &i, &pattern);
		pattern_init(&pattern, RRA, RRB, RRR);
		merge_pattern(moves, &i, &pattern);
		if (i == last_i)
			i++;
		last_i = i;
	}
}

static void	merge_pattern(t_buff *moves, size_t *index, t_pattern *pat)
{
	t_move	curr;
	size_t	i;

	i = *index;
	set_move(&curr, moves, (long)i);
	while (i < moves->len && (curr == pat->a_move || curr == pat->b_move || curr == pat->cumul_move || curr == NO_OP))
	{
		if (curr == pat->a_move)
			pat->a_count++;
		if (curr == pat->b_move)
			pat->b_count++;
		if (curr == pat->cumul_move)
			pat->cumul_count++;
		if (curr == NO_OP)
			pat->no_op_count++;
		i++;
		// fprintf(stderr, "🪄  %s%3zu%s (%s%i%s) a_count = %3zu | b_count = %3zu | cumul_count = %3zu%s\n", YELLOW, *index, GREY, YELLOW, curr, GREY, pat->a_count, pat->b_count, pat->cumul_count, NC);	// TODO: tmp debug
		set_move(&curr, moves, (long)i);
	}
	if (pat->a_count > 0 && pat->b_count > 0)
		convert_pattern(moves, pat, *index);
	*index = i;
}

static void	convert_pattern(t_buff *dst, t_pattern *pat, size_t i)
{
	// size_t	start_index;

	// start_index = i;
	pat->cumul_new = (size_t)min((long)pat->a_count, (long)pat->b_count);
	// fprintf(stderr, "convert_pattern() pat->a_count = %ld | pat->b_count = %ld | pat->cumul_new = %zu\n", pat->a_count, pat->b_count, pat->cumul_new);
	// fprintf(stderr, "%s✦ merged %4zu%s => ", GREEN, pat->cumul_new, GREY);
	pat->cumul_count += pat->cumul_new;
	pat->a_count -= pat->cumul_new;
	pat->b_count -= pat->cumul_new;
	while (pat->cumul_count--)
		dst->data[i++] = (char)pat->cumul_move;
	while (pat->a_count--)
		dst->data[i++] = (char)pat->a_move;
	while (pat->b_count--)
		dst->data[i++] = (char)pat->b_move;
	while (pat->cumul_new--)
		dst->data[i++] = (char)NO_OP;
	while (pat->no_op_count--)
		dst->data[i++] = (char)NO_OP;
	// print_opti_moves(dst, start_index, i - 1, GREY, YELLOW, true);
}
