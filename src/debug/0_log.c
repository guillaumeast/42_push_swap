#include <stdarg.h>
#include "debug.h"

void	log_debug(const char *func_name, size_t depth, const char *message, ...)
{
	va_list args;
	
	va_start(args, message);
	while (depth--)
		fprintf(stderr, "%s>", BOLD_YELLOW);
	fprintf(stderr, "%s> 🔦 %s()%s ", BOLD_YELLOW, func_name, NC);
	vfprintf(stderr, message, args);
	va_end(args);
}

void	print_array_u(uint *array, size_t len, const char *array_color, const char *value_color, uint value, bool nl)
{
	uint	current;
	size_t	i;

	fprintf(stderr, "%s[", array_color);
	i = 0;
	while (i < len)
	{
		current = array[i];
		if (current == value)
			fprintf(stderr, "%s%u%s", value_color, array[i], array_color);
		else
			fprintf(stderr, "%u", array[i]);
		if (i < len - 1)
			fprintf(stderr, " ");
	}
	fprintf(stderr, "]%s", NC);
	if (nl)
		fprintf(stderr, "\n");
}
