/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:14:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:14:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char 	*get_room_name(char *s)
{
	size_t	i;
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

int		add_data(int lt, t_data *dt, char *s, char **file)
{
	char	*line[2];
	int 	res;

	if ((res = 1) == 0 || lt == COMM || lt == IGNORE || lt == FAIL)
		return (lt);
	if (lt == START || lt == END)
	{
		if (get_next_line(0, &line[0]) > 0)
		{
			*file = ft_strjoin_fr_two(*file, concat_strs(line[0], "\n", NULL));
			if (is_room(line[1] = ft_strtrim(line[0])))
				res = add_room(dt, get_room_name(line[1]), lt);
			else
				res = FAIL;
			free(line[1]);
		}
		free(line[0]);
	}
	else if (lt == N_ANTS)
		dt->n_ants = (int)ft_atoi(s);
	else if (lt == ROOM)
		res = add_room(dt, get_room_name(s), lt) ? 1 : 0;
	else if (lt == LINK)
		res = add_link(dt, s);
	return (res);
}
