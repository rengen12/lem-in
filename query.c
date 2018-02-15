/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:26:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:26:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*query_pop(t_way **q)
{
	t_way	*elem;
	t_rooms	*res;

	elem = *q;
	*q = (*q)->next;
	elem->next = NULL;
	res = elem->room;
	free(elem);
	return (res);
}

void	query_pb(t_way **q, t_rooms *room)
{
	t_way	*head;

	if (*q && room)
	{
		head = *q;
		while (head->next)
			head = head->next;
		head->next = create_way_elem(room);
	}
	else if (room)
		*q = create_way_elem(room);
}

void	clear_query(t_way **q)
{
	if (q && *q)
	{
		if ((*q)->next) //test it
			clear_query(&(*q)->next);
		free(*q);
		*q = NULL;
	}
}
