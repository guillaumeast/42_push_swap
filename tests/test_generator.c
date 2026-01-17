#include "libft.h"
#include "config_priv.h"
#include <stddef.h>
#include <stdio.h>

int	main(void)
{
	size_t	i;
	size_t	count;
	uint	*configs;
	char	*binary;

	configs = generate_configs(&count);
	if (!configs)
		return (1);
	i = 0;
	while (i < count)
	{
		binary = ft_ultoa_base((unsigned long)configs[i], "01");
		printf("%32s\n", binary);
		free(binary);
		i++;
	}
	return (0);
}
