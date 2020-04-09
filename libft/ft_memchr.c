/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:29:15 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:29:35 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*strcpy;
	unsigned char	charcpy;

	strcpy = (unsigned char*)s;
	charcpy = (unsigned char)c;
	if (n)
	{
		while (n && --n && charcpy != *strcpy)
			strcpy++;
		return ((charcpy == *strcpy) ? (void*)strcpy : NULL);
	}
	else
		return (NULL);
}
