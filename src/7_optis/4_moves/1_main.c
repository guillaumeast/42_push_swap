#include "libft.h"
#include "opti_moves_priv.h"
# include "debug.h"

static void	prune_no_ops(t_buff *moves);
// static void	print_indexes(size_t write, size_t start, size_t len, size_t moves_len, size_t final_len, size_t highlight_index);

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
	// print_indexes(write_index, start_index, len, moves->len, final_len, 0);
	while (write_index < moves->len)
	{
		start_index = write_index;
		while (start_index < moves->len && moves->data[start_index] == NO_OP)	// set start on the first OP
			start_index++;
		// print_indexes(write_index, start_index, len, moves->len, final_len, 1);
		if (start_index >= moves->len)
			break ;
		len = 1;
		while (start_index + len < moves->len && moves->data[start_index + len] != NO_OP)		// len is set until next NO_OP or EOF
			len++;
		// print_indexes(write_index, start_index, len, moves->len, final_len, 2);
		ft_memmove(moves->data + write_index, moves->data + start_index, len);
		ft_memset(moves->data + write_index + len, (int)NO_OP, start_index - write_index);
		// fprintf(stderr, "%s↤ compressing %s=> ", YELLOW, GREY);
		// print_opti_moves(moves, write_index, start_index + len - 1, GREY, YELLOW, true);
		final_len = write_index + len;
		// print_indexes(write_index, start_index, len, moves->len, final_len, 4);
		write_index += len;
		// print_indexes(write_index, start_index, len, moves->len, final_len, 0);
	}
	while (moves->data[final_len - 1] == NO_OP)
		final_len--;
	// print_indexes(write_index, start_index, len, moves->len, final_len, 3);
	if (final_len >= moves->len)
		return ;
	// fprintf(stderr, "%s✔︎        -%3zu => ", BOLD_GREEN, moves->len - final_len);
	// print_opti_moves(moves, write_index, start_index + len - 1, BOLD_GREEN, BOLD_RED, false);
	// fprintf(stderr, "%s✔︎ moves compressed => %3zu\n%s", BOLD_GREEN, moves->len - final_len, NC);
	moves->len = final_len;
}

// static void	print_indexes(size_t write, size_t start, size_t len, size_t moves_len, size_t final_len, size_t highlight_index)
// {
// 	if (highlight_index == 0)
// 		fprintf(stderr, "🚚%s [write = %s%3zu%s] [start = %3zu] [len = %3zu] [moves->len = %3zu] [final_len = %3zu]%s\n", GREY, YELLOW, write, GREY, start, len, moves_len, final_len, NC);
// 	else if (highlight_index == 1)
// 		fprintf(stderr, "🚚%s [write = %3zu] [start = %s%3zu%s] [len = %3zu] [moves->len = %3zu] [final_len = %3zu]%s\n", GREY, write, YELLOW, start, GREY, len, moves_len, final_len, NC);
// 	else if (highlight_index == 2)
// 		fprintf(stderr, "🚚%s [write = %3zu] [start = %3zu] [len = %s%3zu%s] [moves->len = %3zu] [final_len = %3zu]%s\n", GREY, write, start, YELLOW, len, GREY, moves_len, final_len, NC);
// 	else if (highlight_index == 3)
// 		fprintf(stderr, "🚚%s [write = %3zu] [start = %3zu] [len = %3zu] [moves->len = %s%3zu%s] [final_len = %3zu]%s\n", GREY, write, start, len, YELLOW, moves_len, GREY, final_len, NC);
// 	else if (highlight_index == 4)
// 		fprintf(stderr, "🚚%s [write = %3zu] [start = %3zu] [len = %3zu] [moves->len = %3zu] [final_len = %s%3zu%s]%s\n", GREY, write, start, len, moves_len, YELLOW, final_len, GREY, NC);
// 	else
// 		fprintf(stderr, "🚚%s [write = %3zu] [start = %3zu] [len = %3zu] [moves->len = %3zu] [final_len = %3zu]%s\n", GREY, write, start, len, moves_len, final_len, NC);
// }
