/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:24:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 20:24:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ways_pb(t_data *dt, t_ways *way)
{
	t_ways	*ways;

	ways = dt->ways;
	if (!ways)
		dt->ways = way;
	else
	{
		while (ways->other)
			ways = ways->other;
		ways->other = way;
	}
}

t_way	*create_way_elem(t_rooms *room)
{
	t_way	*res;

	if (!(res = (t_way *)malloc(sizeof(t_way))))
		return (NULL);
	res->next = NULL;
	res->ant = 0;
	res->room = room;
	return (res);
}

void	way_pf(t_way **q, t_rooms *room)
{
	t_way	*head;

	head = create_way_elem(room);
	head->next = *q;
	*q = head;
}
