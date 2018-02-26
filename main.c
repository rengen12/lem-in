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

void		free_room_next(t_rooms **room)
{
	if (room && *room)
	{
		if ((*room)->next)
			free_room_next(&(*room)->next);
		delete_neigh(&(*room)->neigh);
		free((*room)->name);
		free(*room);
		*room = NULL;
	}
}

void		delete_ways(t_ways **ways)
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

static void	delete_structs(t_data *dt)
{
	int	i;

	i = 0;
	delete_ways(&dt->ways);
	while (i < 200)
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

static void	init_data(t_data *dt)
{
	int	i;

	i = 0;
	dt->n_ants = 0;
	dt->st = 0;
	dt->end = 0;
	dt->ways = 0;
	dt->n_ways = 0;
	while (i < 200)
		dt->rooms[i++] = 0;
}

int			main(int ac, char **av)
{
	t_data	dt;
	char	*file;

	init_data(&dt);
	if (!parse(&dt, &file))
	{
		delete_structs(&dt);
		return (1);
	}
	find_ways(&dt);
	if (ac > 1 && !ft_strcmp("-p", av[1]))
		fl_p(dt.ways);
	print_ways(&dt, file, 1);
	delete_structs(&dt);
	return (0);
}
