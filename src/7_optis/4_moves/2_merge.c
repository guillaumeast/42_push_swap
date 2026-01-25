#include "libft.h"
#include "opti_moves_priv.h"
# include "debug.h"

static bool	merge_pattern(t_buff *dst, t_buff *src, size_t *index, t_pattern *pat);

bool	merge_all(t_buff *dst, t_buff *src, size_t *index)
{
	t_pattern	pattern;

	pattern_init(&pattern, SA, SB, SS);
	if (!merge_pattern(dst, src, index, &pattern))
		return (false);
	pattern_init(&pattern, RA, RB, SS);
	if (!merge_pattern(dst, src, index, &pattern))
		return (false);
	pattern_init(&pattern, RRA, RRB, SS);
	if (!merge_pattern(dst, src, index, &pattern))
		return (false);
	pattern_init(&pattern, PA, PB, NO_OP);
	if (!merge_pattern(dst, src, index, &pattern))
		return (false);
	return (true);
}

static bool	merge_pattern(t_buff *dst, t_buff *src, size_t *index, t_pattern *pat)
{
	t_move	curr;

	set_move(&curr, src, (long)index);
	while (*index < src->len && (curr == pat->a_move || curr == pat->b_move || curr == pat->cumul_move || curr == NO_OP))
	{
		if (curr == pat->a_move)
			pat->a_count++;
		if (curr == pat->b_move)
			pat->b_count++;
		if (curr == pat->cumul_move)
			pat->cumul_count++;
		(*index)++;
		set_move(&curr, src, (long)index);
	}
	pat->cumul_new = (size_t)min((long)pat->a_count, (long)pat->b_count);
	if (pat->cumul_new > 0)
		fprintf(stderr, "%s✦ merging %s%3zu moves into %3zu moves (%s-%3zu%s)...%s\n", GREEN, 
			GREY, pat->cumul_count + pat->a_count + pat->b_count,
			pat->cumul_count + pat->a_count + pat->b_count - pat->cumul_new, 
			GREEN, pat->cumul_new, GREY, NC);
	pat->cumul_count += pat->cumul_new;
	pat->a_count -= pat->cumul_new;
	pat->b_count -= pat->cumul_new;
	if (!move_add((char)pat->cumul_move, pat->cumul_count, dst))
		return (false);
	if (!move_add((char)pat->a_move, pat->a_count, dst))
		return (false);
	return (!move_add((char)pat->b_move, pat->b_count, dst));
}
