/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:11:28 by badam             #+#    #+#             */
/*   Updated: 2019/11/10 19:57:17 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "ft_strlen.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*dstcpy;
	char	*srccpy;

	dstcpy = dst;
	srccpy = (char*)src;
	if (!dst || !src)
		return (0);
	if (dstsize)
	{
		while (*srccpy && dstsize && --dstsize)
			*(dstcpy++) = *(srccpy++);
		*dstcpy = '\0';
	}
	return (ft_strlen(src));
}
