/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:40:35 by badam             #+#    #+#             */
/*   Updated: 2019/11/04 20:05:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*ft_itoa(int n)
{
	int		positive;
	long	posinb;
	int		posinbcpy;
	size_t	strlen;
	char	*str;

	positive = (n >= 0);
	strlen = positive ? 2 : 3;
	posinb = positive ? (long)n : (-1 * (long)n);
	posinbcpy = posinb;
	while (posinbcpy / 10)
	{
		posinbcpy /= 10;
		strlen++;
	}
	if (!(str = malloc(sizeof(char) * strlen)))
		return (NULL);
	str[--strlen] = '\0';
	str[0] = '-';
	while ((positive ? strlen : (strlen - 1)) > 0)
	{
		str[--strlen] = '0' + (posinb % 10);
		posinb /= 10;
	}
	return (str);
}
