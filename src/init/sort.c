/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:04:26 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/30 17:09:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	merge_sort(t_sort_data *data, size_t left, size_t right);
static void	merge(t_sort_data *data, size_t left, size_t mid, size_t right);

bool	sort(int **array, size_t size)
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
