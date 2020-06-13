/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:43:03 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:31:34 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
