/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 09:46:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 09:46:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	sharp(char *s)
{
	int	res;

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

static int	is_valid(t_data dt)
{
	if (dt.n_ants <= 0 || !dt.st || !dt.end || dt.st == dt.end)
		return (FAIL);
	return (1);
}

static int	line_type(char *s)
{
	if (s && *s == '#')
		return (sharp(++s));
	else if (s && *s != ' ' && ft_isprint(*s) && *s != 'L')
	{
		if (is_room(s))
			return (ROOM);
		else if (is_link(s))
			return (LINK);
		else if (is_n_ants(s))
			return (N_ANTS);
	}
	return (FAIL);
}

int			parse(t_data *dt, char **file)
{
	char	*line;
	int		res;
	char	*temp;

	res = 1;
	line = NULL;
	*file = (char *)malloc(1);
	*file[0] = '\0';
	while (res && get_next_line(0, &line) > 0)
	{
		if (*line == '-')
			break ;
		*file = ft_strjoin_fr_two(*file, (concat_strs(line, "\n", NULL)));
		temp = ft_strtrim(line);
		res = add_data(line_type(temp), dt, temp, file);
		free(line);
		free(temp);
	}
	if (res)
		free(line);
	if (res != FAIL)
		res = is_valid(*dt);
	if (!res)
		ft_putendl("ERROR");
	return (res);
}
