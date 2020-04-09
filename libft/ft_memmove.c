/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:21:56 by badam             #+#    #+#             */
/*   Updated: 2019/11/10 20:14:28 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "ft_strlen.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstcpy;
	unsigned char	*srccpy;

	if (!dst && !src && len)
		return (NULL);
	dstcpy = (unsigned char*)dst;
	srccpy = (unsigned char*)src;
	if (dstcpy > srccpy && dstcpy < srccpy + len)
	{
		dstcpy += len - 1;
		srccpy += len - 1;
		while ((len--))
			*(dstcpy--) = *(srccpy--);
	}
	else
		while ((len--))
			*(dstcpy++) = *(srccpy++);
	return (dst);
}
