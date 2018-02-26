/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:36:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/19 17:36:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	fl_p(t_ways *ways)
{
	while (ways)
	{
		if (ways->way)
			print_way(ways->way);
		ways = ways->other;
	}
}
