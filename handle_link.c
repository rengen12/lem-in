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

void	add_link(t_data *dt, char *s)
{
	char	*name[2];
	char 	*minsp;
	int 	mins;
	t_rooms	*r1;
	t_rooms	*r2;

	if (!(minsp = ft_strchr(s, '-')))
		return ;
	mins = (int)(minsp - s);
	name[0] = ft_strsub(s, 0, (size_t)mins);
	name[1] = ft_strsub(s, (unsigned)mins + 1, ft_strlen(s) - 1 - mins);
	r1 = add_room(dt, name[0], 1);
	r2 = add_room(dt, name[1], 1);
	if (!have_neigh(r1, r2->name))
		add_neigh(r1, r2);
}