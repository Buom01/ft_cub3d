/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:43:03 by badam             #+#    #+#             */
/*   Updated: 2019/11/05 17:23:53 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char *strcpy;

	strcpy = (unsigned char*)s;
	while (*strcpy)
		strcpy++;
	while (*strcpy != (unsigned char)c && strcpy != (unsigned char*)s)
		strcpy--;
	return (((unsigned char)c == *strcpy) ? (char*)strcpy : NULL);
}
