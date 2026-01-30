/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:09:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 20:09:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GREEDY_PRIV_H
# define GREEDY_PRIV_H

# include "stack.h"
# include <stddef.h>

typedef struct s_raw_cost
{
	size_t	rotate;
	size_t	reverse;
}	t_raw_cost;

typedef struct s_choice
{
	t_raw_cost	opti;
	t_raw_cost	bad;
}	t_choice;

typedef struct s_total
{
	size_t	rr;
	size_t	ra;
	size_t	rb;
	size_t	rrr;
	size_t	rra;
	size_t	rrb;
	size_t	total;
}	t_total;

typedef struct s_insert
{
	size_t	from_index;
	size_t	target_index;
	t_total	cost;
}	t_insert;

t_total	best_cost(const t_stack *a, size_t i_a, const t_stack *b, size_t i_b);

#endif
