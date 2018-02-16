/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:19:00 by amichak           #+#    #+#             */
/*   Updated: 2018/02/15 13:19:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 	is_room(char *s)
{
	char	*cs;
	int 	num;

	num = 0;
	while (s && *s && *s != ' ')
		s++;
	if (!s || *s != ' ')
		return (FAIL);
	s++;
	cs = s;
	*s == '-' ? s++ : NULL;
	if (*s && !ft_isdigit(*s))
		return (FAIL);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s != ' ')
		return (FAIL);
	s++;
	if (!*s || !ft_is_int(ft_atoi(cs)) || !ft_is_int(ft_atoi(s)))
		return (FAIL);
	*s == '-' ? s++ : NULL;
	while (*s && ft_isdigit(*s))
	{
		num = 1;
		s++;
	}
	if (!*s && num)
		return (1);
	return (FAIL);
}

int 	is_link(char *s)
{
	int	f;

	f = 0;
	while (*s && *s != '-' && *s != ' ')
		s++;
	if (*s++ != '-')
		return (FAIL);
	if (!*s || *s == 'L' || *s == '#')
		return (FAIL);
	while (*s && ft_isprint(*s) && *s != ' ')
	{
		f = 1;
		s++;
	}
	if (!*s && f)
		return (1);
	return (FAIL);
}

int 	is_n_ants(char *s)
{
	ssize_t	num;

	num = ft_atoi(s);
	if (num <= 0 || !ft_is_int(num))
		return (FAIL);
	while (*s)
		if (ft_isdigit(*s))
			s++;
		else
			return (FAIL);
	return (1);
}
