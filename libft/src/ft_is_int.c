/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:08:33 by amichak           #+#    #+#             */
/*   Updated: 2017/12/28 17:36:30 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_is_int(ssize_t num)
{
	if (num <= 2147483647 && num >= -2147483648)
		return (1);
	return (0);
}
