/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:24:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:24:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"






void	free_room_next(t_rooms **room)
{
	if (room && *room)
	{
		if ((*room)->next)
			free_room_next(&(*room)->next);
		free(*room);
		*room = NULL;
	}
}

void	delete_ways(t_ways **ways)
{
	if (ways && *ways)
	{
		if ((*ways)->other)
			delete_ways(&(*ways)->other);
		clear_query(&(*ways)->way);
		free(*ways);
		*ways = NULL;
	}
}

void	delete_structs(t_data *dt)
{
	int 	i;

	i = 0;
	delete_ways(&dt->ways);
	while (i < 100)
	{
		if (dt->rooms[i])
		{
			delete_neigh(&dt->rooms[i]->neigh);
			free(dt->rooms[i]->name);
			if (dt->rooms[i]->next)
				free_room_next(&dt->rooms[i]->next);
			free(dt->rooms[i]);
			dt->rooms[i] = NULL;
		}
		i++;
	}
}


/*NU*/
void	print_way(t_way *way)
{
	while (way)
	{
		ft_putstr(way->room->name);
		ft_putstr(" -> ");
		way = way->next;
	}
	ft_putendl("");
}












static void	init_data(t_data *dt)
{
	int 	i;

	i = 0;
	dt->n_ants = 0;
	dt->st = 0;
	dt->end = 0;
	dt->ways = 0;
	dt->n_ways = 0;
	while (i < 100)
		dt->rooms[i++] = 0;
}

int main(void)
{
	t_data	dt;

	init_data(&dt);
	if (!parse(&dt))
	{
		delete_structs(&dt);
		return (1);
	}
	find_ways(&dt);
	print_ways(&dt);
	delete_structs(&dt);
	return (0);
}