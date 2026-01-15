#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_sort_data
{
	int		*array;
	int		*tmp;
}	t_sort_data;

static bool	sort(int *array, size_t size);
static void	merge_sort(t_sort_data *data, size_t left, size_t right);
static void	merge(t_sort_data *data, size_t left, size_t mid, size_t right);
static bool	get_index(int value, const int *array, size_t size, uint *ret);

uint	*normalize(int *array, size_t size)
{
	int		*sorted;
	uint	*res;
	size_t	i;

	sorted = malloc(size * sizeof * sorted);
	if (!sorted)
		return (false);
	ft_memcpy(sorted, array, size * sizeof * array);
	if (!sort(sorted, size))
		return (free(sorted), NULL);
	res = malloc(size * sizeof * res);
	if (!res)
		return (free(sorted), NULL);
	i = 0;
	while (i < size)
	{
		if (!get_index(array[i], sorted, size, &(res[i])))
			return (free(sorted), free(res), NULL);
		i++;
	}
	free(sorted);
	return (res);
}

static bool	sort(int *array, size_t size)
{
	t_sort_data	data;

	data.array = array;
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

static bool	get_index(int value, const int *array, size_t size, uint *ret)
{
	uint	low;
	uint	mid;
	uint	high;

	low = 0;
	high = (uint)size - 1;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (array[mid] == value)
		{
			*ret = mid;
			return (true);
		}
		else if (array[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (false);
}
