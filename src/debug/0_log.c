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
