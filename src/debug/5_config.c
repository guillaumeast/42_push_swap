#include "debug.h"
#include "chunk.h"

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
	if (config->algo_1 == chunk)
		fprintf(stderr, " (chunk_size = %zu)", config->chunk_size);
	fprintf(stderr, "\n");
}
