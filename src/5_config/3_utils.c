#include "libft.h"
#include "config.h"
#include "stack.h"
#include <stdlib.h>

#define CHUNK_N_MIN 2
#define CHUNK_N_MAX 9

bool	get_chunk_sizes(size_t **ret, size_t *ret_size, const t_stack *stack)
{
	size_t	max_size;
	long	size;
	size_t	i;
	size_t	n;

	max_size = (CHUNK_N_MAX - CHUNK_N_MIN + 1) * 2;
	*ret = malloc(max_size * sizeof ** ret);
	if (!*ret)
		return (false);
	i = 0;
	n = CHUNK_N_MIN;
	while (n <= CHUNK_N_MAX)
	{
		size = (long)(stack->len / n);
		if (size > 0 && size < (long)stack->len)
			(*ret)[i++] = (size_t)size;
		size = (long)n * (long)square_root_rounded((int)stack->len);
		if (size > 0 && size < (long)stack->len)
			(*ret)[i++] = (size_t)size;
		n++;
	}
	*ret_size = i;
	return (true);
}

bool	config_dup(t_config *dst, const t_config *src, size_t values_count)
{
	dst->algo_1 = src->algo_1;
	dst->algo_2 = src->algo_2;
	dst->algo_1_name = src->algo_1_name;
	dst->algo_2_name = src->algo_2_name;
	dst->opti_names = src->opti_names;
	dst->opti_lis = src->opti_lis;
	dst->opti_lis_swap = src->opti_lis_swap;
	dst->opti_swap_b = src->opti_swap_b;
	dst->opti_median = src->opti_median;
	dst->chunk_size = src->chunk_size;
	dst->lis.keep = NULL;
	dst->lis.swap = NULL;
	if (!dst->opti_lis)
		return (true);
	dst->lis.start_index = src->lis.start_index;
	dst->lis.keep = src->lis.keep;
	dst->lis.keep_count = src->lis.keep_count;
	dst->lis.swap_count = src->lis.swap_count;
	dst->lis.keep = malloc(values_count * sizeof * dst->lis.keep);
	dst->lis.swap = malloc(values_count * sizeof * dst->lis.swap);
	if (!dst->lis.keep || !dst->lis.swap)
		return (free(dst->lis.keep), free(dst->lis.swap), false);
	ft_memcpy(dst->lis.keep, src->lis.keep, values_count * sizeof * dst->lis.keep);
	ft_memcpy(dst->lis.swap, src->lis.swap, values_count * sizeof * dst->lis.swap);
	return (true);
}

void	config_free(t_config *config)
{
	if (!config->opti_lis)
		return ;
	lis_free(&config->lis);
}
