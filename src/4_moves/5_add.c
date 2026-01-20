#include "libft.h"

bool	move_add(char move, size_t count, t_buff *list)
{
	while (count--)
	{
		if (!buff_append(list, &move, 1))
			return (false);
	}
	return (true);
}
