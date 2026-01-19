#include "debug.h"
#include "chunk.h"

// TMP: remove before submit

/* ---------- config ---------- */

void	config_print_all(t_config_list *configs)
{
	size_t	i;

	i = 0;
	while(i < configs->count)
	{
		config_print(&configs->data[i], i, true);
		i++;
	}
}

void	config_print(t_config *config, size_t index, bool print_index)
{
	if (print_index)
		fprintf(stderr, "⚙️  CONFIG[%zu] => ", index);
	fprintf(stderr, "%s + %s%s\n", config->algo_1_name, config->algo_2_name, config->opti_names);
	if (config->algo_2 == chunk)
		fprintf(stderr, "(chunk_size = %u)", config->chunk.size);
	fprintf(stderr, "\n");
}
