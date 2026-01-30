#include "libft.h"
#include "optimize_priv.h"

static void	prune_no_ops(t_buff *moves);

void	optimize_moves(t_buff *moves)
{
	size_t	prev_len;

	while (true)
	{
		prev_len = moves->len;
		prune_all(moves);
		merge_all(moves);
		prune_no_ops(moves);
		if (moves->len >= prev_len)
			break ;
	}
}

static void	prune_no_ops(t_buff *moves)
{
	size_t	write_index;
	size_t	start_index;
	size_t	len;
	size_t	final_len;

	write_index = 0;
	start_index = 0;
	len = 0;
	final_len = moves->len;
	while (write_index < moves->len && moves->data[write_index] != NO_OP)	// set write on the first NO_OP
		write_index++;
	while (write_index < moves->len)
	{
		start_index = write_index;
		while (start_index < moves->len && moves->data[start_index] == NO_OP)	// set start on the first OP
			start_index++;
		if (start_index >= moves->len)
			break ;
		len = 1;
		while (start_index + len < moves->len && moves->data[start_index + len] != NO_OP)		// len is set until next NO_OP or EOF
			len++;
		ft_memmove(moves->data + write_index, moves->data + start_index, len);
		ft_memset(moves->data + write_index + len, (int)NO_OP, start_index - write_index);
		final_len = write_index + len;
		write_index += len;
	}
	while (final_len > 0 && moves->data[final_len - 1] == NO_OP)
		final_len--;
	if (final_len >= moves->len)
		return ;
	moves->len = final_len;
}
