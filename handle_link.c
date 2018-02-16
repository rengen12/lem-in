/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:23:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:23:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_link(t_data *dt, char *s)
{
	char	*name[2];
	char 	*minsp;
	int 	mins;
	t_rooms	*r1;
	t_rooms	*r2;

	if (!(minsp = ft_strchr(s, '-')))
		return (FAIL);
	mins = (int)(minsp - s);
	name[0] = ft_strsub(s, 0, (size_t)mins);
	name[1] = ft_strsub(s, (unsigned)mins + 1, ft_strlen(s) - 1 - mins);
	//r1 = add_room(dt, name[0], 1);
	//r2 = add_room(dt, name[1], 1);
	r1 = find_room(name[0], *dt);
	r2 = find_room(name[1], *dt);
	free(name[0]);
	free(name[1]);
	if (!r1 || !r2)
		return (FAIL);
	if (!have_neigh(r1, r2->name))
		add_neigh(r1, r2);
	return (1);
}