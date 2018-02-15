/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:16:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:16:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		hash_func(char *s)
{
	int 	res;

	res = 0;
	while (*s)
		res += *s++;
	return (res % 100);
}

static t_rooms	*find_room(char *name, t_data dt)
{
	t_rooms	*res;

	res = NULL;
	if (name)
	{
		res = dt.rooms[hash_func(name)];
		while (res && ft_strcmp(name, res->name))
			res = res->next;
	}
	return (res);
}

static t_rooms	*creat_room(void)
{
	t_rooms	*room;

	if (!(room = (t_rooms *)malloc(sizeof(t_rooms))))
		return (NULL);
	*room = (t_rooms){0, 0, 0, 0, 0, 0};
	return (room);
}

static int		is_room_exist(char *name, t_data dt)
{
	t_rooms	*room;

	room = find_room(name, dt);
	if (room)
		return (1);
	return (0);
}

t_rooms			*add_room(t_data *dt, char *name, int lt)
{
	int 	hf;
	t_rooms	*room;

	if (!name || !*name)
		return (NULL);
	if (is_room_exist(name, *dt))
	{
		room = find_room(name, *dt);
		free(name);
		return (room);
	}
	if (!(room = creat_room()))
		return (NULL);
	room->name = name;
	hf = hash_func(name);
	room->next = dt->rooms[hf];
	dt->rooms[hf] = room;
	if (lt == START)
		dt->st = room;
	else if (lt == END)
		dt->end = room;
	return (room);
}
