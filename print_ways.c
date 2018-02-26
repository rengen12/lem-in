/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ways.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:31:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:31:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_way	**arr_way(t_ways *ways, int nways)
{
	t_way	**res;
	int		i;

	i = 1;
	if (!(res = (t_way **)malloc(sizeof(t_way *) * (nways + 1))))
		return (NULL);
	res[0] = NULL;
	while (ways)
	{
		res[i++] = ways->way;
		ways = ways->other;
	}
	return (res);
}

static int		*mway_l(t_ways *ways, int nw)
{
	int		*res;
	int		i;

	i = 1;
	if (!(res = ft_arrnew(nw + 1)))
		return (NULL);
	res[0] = nw;
	while (i <= nw)
	{
		res[i++] = ways->depth;
		ways = ways->other;
	}
	return (res);
}

void			ants_walk(int *f, t_data *dt, t_ant *cants)
{
	if (cants->room->next && cants->room->next->ant == 0)
	{
		cants->room->ant = 0;
		cants->room = cants->room->next;
		if (cants->room->room != dt->end)
			cants->room->ant = 1;
		if (*f == 1)
			ft_putchar(' ');
		ft_putchar('L');
		ft_putnbr(cants->n_ant);
		ft_putchar('-');
		ft_putstr(cants->room->room->name);
		*f = 1;
	}
}

static void		handle_file(char *file)
{
	ft_putendl(file);
	free(file);
}

void			print_ways(t_data *dt, char *file, int f)
{
	t_ant	*ants;
	t_ant	*cants;

	if (!dt->ways)
		ft_putendl("ERROR");
	else
	{
		handle_file(file);
		if (!(ants = handle_ants(dt->n_ants, mway_l(dt->ways, dt->n_ways), \
					arr_way(dt->ways, dt->n_ways))))
			return ;
		while (f)
		{
			f = 0;
			cants = ants;
			while (cants)
			{
				ants_walk(&f, dt, cants);
				cants = cants->next;
			}
			if (f)
				ft_putchar('\n');
		}
		delete_ants(&ants);
	}
}
