#include <stdio.h>
#include "lem_in.h"

int 	ft_is_int(ssize_t num)
{
	if (num <= 2147483647 && num >= -2147483648)
		return (1);
	return (0);
}

int 	hash_func(char *s)
{
	int 	res;

	res = 0;
	while (*s)
		res += *s++;
	return (res % 100);
}

void	add_room(t_data *dt, char *s, int lt)
{

}

void	add_link(t_data *dt, char *s, int lt)
{

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
		dt->n_ants = ft_atoi(s);
		if (!ft_is_int(dt->n_ants))
			return (FAIL);
	}
	else if (lt == ROOM)
		add_room(dt, s, lt);
	else if (lt == LINK)
		add_link(dt, s, lt);
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
	if (!ft_is_int(ft_atoi(s))
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
	//validate names
	//one minus
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
			return (0);
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
	return (res);
}

void	init_struct(t_data *dt)
{
	int 	i;

	i = 0;
	dt->st = 0;
	dt->end = 0;
	dt->ways = 0;
	while (i < 100)
		dt->rooms[i++] = 0;
}

void	delete_struct(t_data *dt)
{

}

void	find_way(t_data *dt)
{

}

int main(void)
{
	t_data	dt;

	init_struct(&dt);
	if (!parse(&dt))
	{
		delete_struct(&dt);
		return (1);
	}
	find_way(&dt);
	return (0);
}