/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:04:22 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/30 17:31:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static bool		parse_splitted_args(char ***args, t_stack *a);
static size_t	get_total_count(char ***args);
static bool		is_numeric(char *arg);
static bool		is_unique(int nb, t_stack *stack);
static void		free_splitted_args(char ***args);

bool	parse_args(int argc, char **argv, t_stack *a, t_stack *b)
{
	size_t	i;
	char	***args;
	bool	res;

	args = malloc((size_t)argc * sizeof * args);
	if (!args)
		return (false);
	i = 1;
	while (i < (size_t)argc)
	{
		args[i - 1] = ft_split(argv[i], ' ');
		if (!args[i - 1])
			break ;
		i++;
	}
	args[i - 1] = NULL;
	res = stack_init(a, b, get_total_count(args));
	if (res)
		res = parse_splitted_args(args, a);
	free_splitted_args(args);
	return (res);
}

static size_t	get_total_count(char ***args)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	res = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			res++;
			j++;
		}
		i++;
	}
	return (res);
}

static bool	parse_splitted_args(char ***args, t_stack *a)
{
	size_t	i;
	size_t	j;
	long	tmp;

	i = 0;
	while (args[i])
	{
		if (!args[i][0])
			return (false);
		j = 0;
		while (args[i][j])
		{
			if (!is_numeric(args[i][j]) || ft_strlen(args[i][j]) > 11)
				return (false);
			tmp = ft_atol(args[i][j]);
			if (tmp < INT_MIN || tmp > INT_MAX)
				return (false);
			if (!is_unique((int)tmp, a))
				return (false);
			a->values[a->count++] = (int)tmp;
			j++;
		}
		i++;
	}
	return (true);
}

static bool	is_numeric(char *arg)
{
	size_t	i;

	if (arg[0] != '-' && arg[0] != '+' && (arg[0] < '0' || arg[0] > '9'))
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_unique(int nb, t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->count)
	{
		if (stack->values[i] == nb)
			return (false);
		i++;
	}
	return (true);
}

static void	free_splitted_args(char ***args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			free(args[i][j++]);
		free(args[i++]);
	}
	free(args);
}
