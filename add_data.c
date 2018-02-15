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

int		add_data(int lt, t_data *dt, char *s)
{
	char	*line;
	char 	*temp;
	int 	res;

	if ((res = 1) == 0 || lt == COMM || lt == IGNORE || lt == FAIL)
		return (lt);
	if (lt == START || lt == END)
	{
		if (get_next_line(0, &line) > 0)
		{
			if (is_room(temp = ft_strtrim(line)))
				res = add_room(dt, get_room_name(temp), lt) ? 1 : 0;
			else
				res = FAIL;
			free(temp);
		}
		free(line);
	}
	else if (lt == N_ANTS)
		dt->n_ants = (int)ft_atoi(s);
	else if (lt == ROOM)
		res = add_room(dt, get_room_name(s), lt) ? 1 : 0;
	else if (lt == LINK)
		add_link(dt, s);
	return (res);
}
