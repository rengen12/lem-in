/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_way.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:28:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:28:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ways	*create_way(t_rooms *tail)
{
	t_ways	*res;

	if (!(res = (t_ways *)malloc(sizeof(t_ways))))
		return (NULL);
	res->depth = tail->depth;
	res->other = NULL;
	res->way = NULL;
	while (tail)
	{
		tail->stat = BLKD;
		way_pf(&res->way, tail);
		tail = tail->prev;
	}
	return (res);
}

static t_ways	*find_way(t_rooms *cur, t_rooms *end, t_way **q)
{
	t_ways	*way;

	way = NULL;
	cur->stat = VSTD;
	if (cur == end)
		return (create_way(cur));
	handle_neigh(q, cur);
	if (*q)
		way = find_way(query_pop(q), end, q);
	return (way);
}

static void	reset_to_default(t_data *dt)
{
	int i;

	i = 0;
	dt->end->prev = 0;
	dt->end->stat = NVSTD;
	while (i < 200)
	{
		if (dt->rooms[i] && dt->rooms[i]->stat != BLKD)
		{
			dt->rooms[i]->stat = NVSTD;
			dt->rooms[i]->depth = 0;
			dt->rooms[i]->prev = 0;
		}
		i++;
	}
}

static int	count_num_ways(t_ways *ways)
{
	int 	i;

	i = 0;
	while (ways)
	{
		i++;
		ways = ways->other;
	}
	return (i);
}

void		find_ways(t_data *dt)
{
	t_way	*q;
	t_ways	*res;

	q = NULL;
	while (1)
	{
		res = find_way(dt->st, dt->end, &q);
		clear_query(&q);
		reset_to_default(dt);
		if (!res)
			break ;
		ways_pb(dt, res);
		if (res->depth < 2)
			break ;
	}
	if (dt->ways)
		dt->n_ways = count_num_ways(dt->ways);
}
