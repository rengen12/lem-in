#include <stdio.h>
#include "lem_in.h"

void 	reset_to_default(t_data *dt)//delete prev and stat int rooms
{
	int i;

	i = 0;
	dt->end->prev = 0;
	dt->end->stat = NVSTD;
	while (i < 100)
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

	if (!name || !*name || *name == 'L')
		return (NULL);
	if (is_room_exist(name, *dt))
		return (find_room(name, *dt));
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
	n1 = ft_strsub(s, 0, (size_t)mins);
	n2 = ft_strsub(s, (unsigned)mins + 1, ft_strlen(s) - 1); //если одинаков
	//if (!(r1 = find_room(n1, *dt)))
		r1 = add_room(dt, n1, 1);
	//if (!(r2 = find_room(n2, *dt)))
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
	int 	res;

	res = 1;
	if (lt == COMM || lt == IGNORE || lt == FAIL)
		return (lt);
	if (lt == START || lt == END)
	{
		if (get_next_line(0, &line) > 0) // add validate
		{
			temp = ft_strtrim(line);
			if (is_room(temp))
				res = add_room(dt, get_room_name(temp), lt) ? 1 : 0;
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
		res = add_room(dt, get_room_name(s), lt) ? 1 : 0;
	else if (lt == LINK)
		add_link(dt, s, lt);
	return (res);
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

int 	is_valid(t_data dt)
{
	if (dt.n_ants <= 0)
	{
		ft_puterr("Wrong number of ants");
		return (FAIL);
	}
	if (!dt.st)
	{
		ft_puterr("Start doesn't exist");
		return (FAIL);
	}
	if (!dt.end)
	{
		ft_puterr("End doesn't exist");
		return (FAIL);
	}
	if (dt.st == dt.end)
	{
		ft_puterr("Start is equivalent to end");
		return (FAIL);
	}
	return (1);
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
		if (*line == '-')
		{
			//free(line);
			break ;
		}
		temp = ft_strtrim(line);
		res = add_data(line_type(temp), dt, temp);
		free(line);
		free(temp);
	}
	free(line);
	if (res != FAIL)
		res = is_valid(*dt);
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

void	clear_query(t_way **q)
{
	if (*q)
	{
		if ((*q)->next) //test it
			clear_query(&(*q)->next);
		free(*q);
		*q = NULL;
	}
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

void	query_pf(t_way **q, t_rooms *room)
{
	t_way	*head;

	head = create_way_elem(room);
	head->next = *q;
	*q = head;
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

t_ways	*create_way(t_way **way, t_rooms *tail)
{
	t_ways	*res;

	if (!(res = (t_ways *)malloc(sizeof(t_ways))))
		return (NULL);
	res->depth = tail->depth;
	res->other = NULL;
	res->way = NULL;
	//clear_query(way);
	//*way = NULL;
	while (tail)
	{
		tail->stat = BLKD;
		query_pf(&res->way, tail);
		tail = tail->prev;
	}
	return (res);
}

t_ways	*find_way(t_rooms *cur, t_rooms *end, t_rooms *prev, t_way **q)
{
	t_ways	*way;

	way = NULL;
	cur->stat = VSTD;
	if (cur == end)
		return (create_way(q, cur));
	handle_neigh(q, cur);
	if (*q)
		way = find_way(query_pop(q), end, cur, q);
	return (way);
}

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

void	find_ways(t_data *dt)
{
	t_way	*q;
	t_ways	*res;

	q = NULL;
	while (1)
	{
		res = find_way(dt->st, dt->end, 0, &q);
		clear_query(&q);
		reset_to_default(dt);
		if (!res)
			break ;
		ways_pb(dt, res);
		if (res->depth < 2)
			break ;
	}
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
		ft_putendl(dt.rooms[i] ? dt.rooms[i]->name : "-");
		if (dt.rooms[i] && dt.rooms[i]->next)
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

int 	count_iter_for_way(int depth, int qant)
{
	if (qant <= 0 || depth <= 0)
		return (0);
	return (depth + qant - 1);
}

int 	*calculate_parallel(t_data *dt, int nw, int n_ants)
{
	int	*res;
	int 	i;

	if (!(res = ft_arrnew(nw + 1)))
		return (NULL);
	res[0] = nw;
	while (n_ants > 0)
	{
		i = 1;
		while (i <= nw)
		{
			res[i++]++;
			n_ants--;
			if (res[i])
		}
	}
	return (res);
}

int 	count_num_ways(t_ways *ways)
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

void	handle_ants(t_data *dt)
{
	t_ant	*ants;

	if (!(ants = (t_ant *)malloc(sizeof(t_ant))))
		return ;
	calculate_parallel(dt, count_num_ways(dt->ways), dt->n_ants);
}

void	print_ways(t_data *dt)
{
	t_ways *ways;

	if (!dt->ways)
		ft_puterr("No way was found");
	else
	{
		handle_ants(dt);
		/*ways = dt.ways;
		while (ways)
		{
			print_way(ways->way);
			ways = ways->other;
		}*/
	}
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