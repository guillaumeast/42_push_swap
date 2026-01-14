#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_sort_data
{
	int		*array;
	int		*tmp;
}	t_sort_data;

static bool	sort(int **array, size_t size);
static void	merge_sort(t_sort_data *data, size_t left, size_t right);
static void	merge(t_sort_data *data, size_t left, size_t mid, size_t right);
static int	get_index(int value, const int *array, size_t size);

bool	normalize(int *array, size_t size)
{
	int		*tmp;
	size_t	i;

	tmp = malloc(size * sizeof * tmp);
	if (!tmp)
		return (false);
	ft_memcpy(tmp, array, size * sizeof * array);
	if (!sort(&tmp, size))
		return (false);
	i = 0;
	while (i < size)
	{
		array[i] = get_index(array[i], tmp, size);
		if (array[i] == -1)
			return (free(tmp), false);
		i++;
	}
	free(tmp);
	return (true);
}

static bool	sort(int **array, size_t size)
{
	t_sort_data	data;

	data.array = *array;
	data.tmp = malloc(size * sizeof * data.tmp);
	if (!data.tmp)
		return (false);
	merge_sort(&data, 0, size - 1);
	free(data.tmp);
	return (true);
}

static void	merge_sort(t_sort_data *data, size_t left, size_t right)
{
	size_t	mid;

	if (left >= right)
		return ;
	mid = left + (right - left) / 2;
	merge_sort(data, left, mid);
	merge_sort(data, mid + 1, right);
	merge(data, left, mid, right);
}

static void	merge(t_sort_data *data, size_t left, size_t mid, size_t right)
{
	size_t	left_i;
	size_t	right_i;
	size_t	tmp_i;
	size_t	len_to_sort;

	left_i = left;
	right_i = mid + 1;
	tmp_i = 0;
	len_to_sort = right - left + 1;
	while (tmp_i < len_to_sort)
	{
		if (left_i > mid)
			data->tmp[tmp_i] = data->array[right_i++];
		else if (right_i > right)
			data->tmp[tmp_i] = data->array[left_i++];
		else if (data->array[left_i] < data->array[right_i])
			data->tmp[tmp_i] = data->array[left_i++];
		else
			data->tmp[tmp_i] = data->array[right_i++];
		tmp_i++;
	}
	tmp_i = 0;
	while (tmp_i < len_to_sort)
		data->array[left++] = data->tmp[tmp_i++];
}

static int	get_index(int value, const int *array, size_t size)
{
	size_t	low;
	size_t	mid;
	size_t	high;

	low = 0;
	high = size - 1;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (array[mid] == value)
			return ((int)mid);
		else if (array[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (-1);
}
