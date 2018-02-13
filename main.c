#include <stdio.h>
#include "lem_in.h"

void 	reset_to_default(t_data *dt)//delete prev and stat int rooms
{

}

int 	hash_func(char *s)
{
	int 	res;

	res = 0;
	while (*s)
		res += *s++;
	return (res % 100);
}

t_rooms	*find_room(char *name, t_data dt)
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

char 	*get_room_name(char *s)
{
	int 	i;
	char 	*res;

	i = 0;
	while (s[i] != ' ')
		i++;
	if (!(res = ft_strnew(i)))
		return (NULL);
	i = 0;
	while (*s != ' ')
		res[i++] = *s++;
	return (res);
}

t_rooms	*creat_room(void)
{
	t_rooms	*room;

	if (!(room = (t_rooms *)malloc(sizeof(t_rooms))))
		return (NULL);
	*room = (t_rooms){0, 0, 0, 0, 0, 0};
}

int		is_room_exist(char *name, t_data dt)
{
	t_rooms	*room;

	room = find_room(name, dt);
	if (room)
		return (1);
	return (0);
}

t_rooms	*add_room(t_data *dt, char *name, int lt)
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

int 	have_neigh(t_rooms *room, char *name)
{
	t_neigh	*neigh;

	if (!room)
		return (0);
	neigh = room->neigh;
	while (neigh)
	{
		if (!ft_strcmp(neigh->room->name, name))
			return (1);
		neigh = neigh->next;
	}
	return (0);
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
	new1->next = r2->neigh;
	r2->neigh = new1;
	new2->room = r2;
	new2->next = r1->neigh;
	r1->neigh = new2;
}

void	add_link(t_data *dt, char *s, int lt)
{
	char	*n1;
	char	*n2;
	char 	*minsp;
	int 	mins;
	t_rooms	*r1;
	t_rooms	*r2;

	if (!(minsp = ft_strchr(s, '-')))
		return ;
	mins = (int)(minsp - s);
	n1 = ft_strsub(s, 0, mins);
	n2 = ft_strsub(s, mins + 1, ft_strlen(s)); //если одинаков
	if (!(r1 = find_room(n1, *dt)))
		r1 = add_room(dt, n1, 1);
	if (!(r2 = find_room(n2, *dt)))
		r2 = add_room(dt, n2, 1); //may delete this cond
	if (!have_neigh(r1, n2))
		add_neigh(r1, r2);
	//if (!have_neigh(r2, n1))
	//	add_neigh();
}

int		add_data(int lt, t_data *dt, char *s)
{
	char	*line;
	char 	*temp;

	if (lt == COMM || lt == IGNORE || lt == FAIL)
		return (lt);
	if (lt == START || lt == END)
	{
		if (get_next_line(0, &line) > 0) // add validate
		{
			temp = ft_strtrim(line);
			if (is_room(temp))
				add_room(dt, temp, lt);
			else
			{
				free(temp);
				free(line);
				return (FAIL);
			}
			free(temp);
		}
		free(line);
	}
	else if (lt == N_ANTS)
	{
		dt->n_ants = (int)ft_atoi(s);
		if (!ft_is_int(dt->n_ants))
			return (FAIL);
	}
	else if (lt == ROOM)
		add_room(dt, get_room_name(s), lt);
	else if (lt == LINK)
		add_link(dt, s, lt);
	return (1);
}

int 	is_room(char *s)
{
	int 	sp;
	int 	fl;

	fl = 0;
	sp = 0;
	while (*s && *s != ' ')
		s++;
	if (*s == ' ')
		sp++;
	while (*s && *s == ' ')
		s++;
	if (!ft_is_int(ft_atoi(s)))
		return (FAIL);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s == ' ')
		sp++;
	while (*s && *s == ' ')
		s++;
	if (!ft_is_int(ft_atoi(s)))
		return (FAIL);
	while (*s && ft_isdigit(*s))
	{
		s++;
		fl = 1;
	}
	if (fl && sp == 2 && !*s)
		return (1);
	return (FAIL);
}

int 	is_link(char *s)
{
	int	res;

	res = 0;
	while (*s && *s != '-')
		s++;
	if (*s == '-')
		res = 1;
	while (*s && !ft_issptab(*s))
	{
		res = 2;
		s++;
	}
	if (!*s && res == 2)
		return (1);
	return (FAIL);
}

int 	is_n_ants(char *s)
{
	while (*s)
		if (ft_isdigit(*s))
			s++;
		else
			return (FAIL);
	return (1);
}


int 	sharp(char *s)
{
	int 	res;

	res = IGNORE;
	if (*s == '#')
	{
		if (!ft_strcmp(s + 1, "start"))
			res = START;
		else if (!ft_strcmp(s + 1, "end"))
			res = END;
		return (res);
	}
	return (COMM);
}

int 	line_type(char *s)
{
	if (*s == '#')
		return (sharp(++s));
	else if (*s != ' ' && ft_isprint(*s))
	{
		if (is_room(s))
			return (ROOM);
		else if (is_link(s))
			return (LINK);
		else if (is_n_ants(s))
			return (N_ANTS);
	}
	ft_puterr("ERROR");
	ft_puterr(s);
	return (FAIL);
}

int 	parse(t_data *dt)
{
	char	*line;
	int 	res;
	char 	*temp;

	res = 1;
	line = NULL;
	while (res && get_next_line(0, &line) > 0)
	{
		temp = ft_strtrim(line);
		res = add_data(line_type(temp), dt, temp);
		free(line);
		free(temp);
	}
	//need free(line)??
	//write func is_valid
	return (res);
}

void	init_data(t_data *dt)
{
	int 	i;

	i = 0;
	dt->n_ants = 0;
	dt->st = 0;
	dt->end = 0;
	dt->ways = 0;
	while (i < 100)
		dt->rooms[i++] = 0;
}

void	delete_struct(t_data *dt)
{

}

void	find_ways(t_data *dt)
{

}

void	print_data(t_data dt)
{
	int 	i;

	i = 0;
	ft_putstr("n ants = ");
	ft_putnbr(dt.n_ants);
	ft_putendl("");
	ft_putstr("st = ");
	ft_putendl(dt.st->name);
	ft_putstr("end = ");
	ft_putendl(dt.end->name);
	ft_putendl("rooms");
	while (i < 100)
	{
		t_rooms *temp;

		ft_putnbr(i);
		ft_putendl("");
		ft_putendl(dt.rooms[i]->name);
		if (dt.rooms[i]->next)
			temp = dt.rooms[i]->next;
		else
			temp = NULL;
		while (temp)
		{
			ft_putendl(temp->name);
			temp = dt.rooms[i]->next;
		}
		i++;
	}
}

int main(void)
{
	t_data	dt;

	init_data(&dt);
	if (!parse(&dt))
	{
		delete_struct(&dt);
		return (1);
	}
	print_data(dt);
	find_ways(&dt);
	return (0);
}