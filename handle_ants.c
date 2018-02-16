/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:33:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:33:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	qit(int depth, int qant)
{
	if (qant <= 0 || depth <= 0)
		return (0);
	return ((size_t)(depth + qant - 1));
}

static int		*calc_parallel(int *lways, int n_ants)
{
	int	*r;
	int i;

	if (!(r = ft_arrnew(lways[0] + 1)))
		return (NULL);
	r[0] = lways[0];
	while (n_ants > 0)
	{
		i = 1;
		r[i++]++;
		n_ants--;
		if (lways[0] == 1)
		{
			r[1] += n_ants;
			n_ants = 0;
		}
		while (i <= lways[0])
		{
			if (n_ants > 0 && qit(lways[1], r[1]) >= qit(lways[i], r[i] + 1))
			{
				r[i]++;
				n_ants--;
			}
			i++;
		}
	}
	free(lways);
	return (r);
}

static void		add_ant(t_ant **ants, t_way *w)
{
	t_ant	*new;
	t_ant	*t;

	if (!ants || !(new = (t_ant *)malloc(sizeof(t_way))))
		return ;
	new->n_ant = 1;
	new->room = w;
	new->next = NULL;
	if (!*ants)
		*ants = new;
	else
	{
		t = *ants;
		while (t->next)
			t = t->next;
		new->n_ant = t->n_ant + 1;
		t->next = new;
	}
}

t_ant			*handle_ants(int n_ants, int *lways, t_way **mway)
{
	int 	*ant_f_w;
	t_ant	*ants;
	int 	i;

	if ((ants = NULL) != NULL || !lways || !mway)
		return (NULL);
	if (!(ant_f_w = calc_parallel(lways, n_ants)))
		return (NULL);
	while (n_ants > 0)
	{
		i = 1;
		while (i <= ant_f_w[0])
		{
			if (n_ants > 0 && ant_f_w[i] > 0)
			{
				add_ant(&ants, mway[i]);
				n_ants--;
				ant_f_w[i]--;
			}
			i++;
		}
	}
	free(ant_f_w);
	free(mway);
	return (ants);
}