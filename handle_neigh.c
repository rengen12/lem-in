/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_neigh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:24:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:24:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 	have_neigh(t_rooms *room, char *name)
{
	t_neigh	*neigh;

	if (!room || !name || !*name)
		return (0);
	neigh = room->neigh;
	while (neigh)
	{
		if (neigh->room && !ft_strcmp(neigh->room->name, name))
			return (1);
		neigh = neigh->next;
	}
	return (0);
}

void	neigh_pb(t_rooms *room, t_neigh *neigh)
{
	t_neigh	*t;

	if (!room->neigh)
		room->neigh = neigh;
	else
	{
		t = room->neigh;
		while (t->next)
			t = t->next;
		t->next = neigh;
	}
}

void	add_neigh(t_rooms *r1, t_rooms *r2)
{
	t_neigh *new1;
	t_neigh *new2;

	if (!(new1 = (t_neigh *)malloc(sizeof(t_neigh))))
		return ;
	if (!(new2 = (t_neigh *)malloc(sizeof(t_neigh))))
	{
		free (new1);
		return ;
	}
	new1->room = r1;
	new1->next = NULL;
//	new1->next = r2->neigh;
//	r2->neigh = new1;
	neigh_pb(r2, new1);
	new2->room = r2;
	new2->next = NULL;
//	new2->next = r1->neigh;
//	r1->neigh = new2;
	neigh_pb(r1, new2);

}

void	delete_neigh(t_neigh **neigh)
{
	if (neigh && *neigh)
	{
		delete_neigh(&(*neigh)->next);
		free(*neigh);
		*neigh = NULL;
	}
}

void	handle_neigh(t_way **q, t_rooms *cur)
{
	t_neigh	*neigh;

	neigh = cur->neigh;
	while (neigh)
	{
		if (neigh->room->stat == NVSTD)
		{
			neigh->room->stat = WTNG;
			neigh->room->depth = cur->depth + 1;
			neigh->room->prev = cur;
			query_pb(q, neigh->room);
		}
		neigh = neigh->next;
	}
}
