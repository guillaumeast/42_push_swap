#include "config.h"

int main(void)
{
	t_config	**list;

	list = config_get_list();
	config_list_free(&list);
	return (0);
}
