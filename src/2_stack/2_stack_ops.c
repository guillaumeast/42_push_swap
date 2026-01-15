#include "libft.h"
#include "stack.h"

void	stack_rotate(t_stack *stack, size_t count)
{
	stack->offset = (stack->offset + count) % stack->len;
}

void	stack_reverse_rotate(t_stack *stack, size_t count)
{
	stack->offset = modulo((long)stack->offset - (long)count, stack->len);
}

void	stack_swap(t_stack *stack)
{
	size_t	next_index;
	uint	tmp;

	next_index = (stack->offset + 1) % stack->len;
	tmp = stack->data[stack->offset];
	stack->data[stack->offset] = stack->data[next_index];
	stack->data[next_index] = tmp;
}

void	stack_push(t_stack *from, t_stack *to, size_t count)
{
	uint	*dst_ptr;
	uint	*src_ptr;
	size_t	len_to_move;

	while (count--)
	{
		src_ptr = to->data + to->offset;
		dst_ptr = src_ptr + 1;
		len_to_move = (to->len - to->offset) * sizeof * (to->data);
		ft_memmove(dst_ptr, src_ptr, len_to_move);
		to->data[to->offset] = from->data[from->offset];
		to->len++;
		if (from->offset != from->len - 1)
		{
			dst_ptr = from->data + from->offset;
			src_ptr = dst_ptr + 1;
			len_to_move = (from->len - from->offset - 1) * sizeof * (from->data);
			ft_memmove(dst_ptr, src_ptr, len_to_move);
		}
		else
			from->offset = 0;
		from->len--;
	}
}
