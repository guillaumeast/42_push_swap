/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:09:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/04 23:48:13 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GREEDY_PRIV_H
# define GREEDY_PRIV_H

# include <stddef.h>
# include <sys/types.h>

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
	uint	from_value;
	size_t	from_index;
	size_t	target_index;
	t_total	cost;
}	t_insert;

#endif
