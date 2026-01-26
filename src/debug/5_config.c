#include "debug.h"
#include "config_priv.h"
#include "chunk.h"
#include "k_sort.h"

void	config_print_all(const t_configs *configs)
{
	size_t	i;

	i = 0;
	while(i < configs->count)
	{
		config_print(&configs->data[i], i, true);
		i++;
	}
}

void	config_print(const t_config *config, size_t index, bool print_index)
{
	if (print_index)
		fprintf(stderr, "⚙️  CONFIG[%zu] => ", index);
	fprintf(stderr, "%s + %s%s", config->algo_1_name, config->algo_2_name, config->opti_names);
	if (config->algo_1 == chunk || config->algo_1 == k_sort)
		fprintf(stderr, " (chunk_size = %zu)", config->chunk_size);
	fprintf(stderr, "\n");
}

/* -------------------- print raw configs -------------------- */

void	config_print_raw(const uint *configs, size_t count, const char *color, const char *item_color, bool nl)
{
	config_print_algo_1(configs, count, color, item_color, false);
	fprintf(stderr, "%s x %s", color, NC);
	config_print_algo_2(configs, count, color, item_color, false);
	fprintf(stderr, "%s x %s", color, NC);
	config_print_optis(configs, count, color, item_color, false);
	if (nl)
		fprintf(stderr, "\n");
}

void	config_print_algo_1(const uint *configs, size_t count, const char *color, const char *item_color, bool nl)
{
	size_t	i;
	uint	algo;
	uint	seen;
	bool	is_first;

	fprintf(stderr, "%s[", color);
	i = 0;
	seen = 0;
	is_first = true;
	while (i < count)
	{
		algo = (configs[i] & ALGO_1_MASK);
		if ((algo & seen) == 0)
		{
			if (is_first)
				is_first = false;
			else
				fprintf(stderr, "%s ⊗ ", color);
			if (algo == NAIVE)
				fprintf(stderr, "%sNAIVE%s", item_color, NC);
			else if (algo == CHUNK)
				fprintf(stderr, "%sCHUNK%s", item_color, NC);
			else if (algo == K_SORT)
				fprintf(stderr, "%sKSORT%s", item_color, NC);
			else
				fprintf(stderr, "%s%5u%s", BOLD_RED, algo, color);
			seen |= algo;
		}
		i++;
	}
	fprintf(stderr, "%s]%s", color, NC);
	if (nl)
		fprintf(stderr, "\n");
}

void	config_print_algo_2(const uint *configs, size_t count, const char *color, const char *item_color, bool nl)
{
	size_t	i;
	uint	algo;
	uint	seen;
	bool	is_first;

	fprintf(stderr, "%s[", color);
	i = 0;
	seen = 0;
	is_first = true;
	while (i < count)
	{
		algo = (configs[i] & ALGO_2_MASK);
		if ((algo & seen) == 0)
		{
			if (is_first)
				is_first = false;
			else
				fprintf(stderr, "%s ⊗ ", color);
			if (algo == GREEDY)
				fprintf(stderr, "%sGREEDY%s", item_color, NC);
			else
				fprintf(stderr, "%s%5u%s", BOLD_RED, algo, color);
			seen |= algo;
		}
		i++;
	}
	fprintf(stderr, "%s]%s", color, NC);
	if (nl)
		fprintf(stderr, "\n");
}

void	config_print_optis(const uint *configs, size_t count, const char *color, const char *item_color, bool nl)
{
	size_t	i;
	uint	opti;
	uint	seen;
	bool	is_first;

	fprintf(stderr, "%s[", color);
	i = 0;
	seen = 0;
	is_first = true;
	while (i < count)
	{
		opti = (configs[i] & OPTI_MASK);
		if (opti != 0 && (opti & seen) == 0)
		{
			if (is_first)
				is_first = false;
			else
				fprintf(stderr, "%s ⊗ ", color);
			if (opti == MEDIAN)
				fprintf(stderr, "%sMEDIAN%s", item_color, NC);
			else if (opti == LIS)
				fprintf(stderr, "%sLIS%s", item_color, NC);
			else if (opti == LIS_SWAP)
				fprintf(stderr, "%sLIS_SWAP%s", item_color, NC);
			else if (opti == SWAP)
				fprintf(stderr, "%sSWAP%s", item_color, NC);
			else
				fprintf(stderr, "%s%5u%s", BOLD_RED, opti, color);
			seen |= opti;
		}
		i++;
	}
	fprintf(stderr, "%s]%s", color, NC);
	if (nl)
		fprintf(stderr, "\n");
}
