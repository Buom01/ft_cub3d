/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:16:46 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:21:04 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dstcpy;
	char	*srccpy;
	size_t	dstlen;
	size_t	srclen;
	size_t	dstsizecpy;

	dstcpy = (char*)dst;
	srccpy = (char*)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize && (dstsizecpy = dstsize - dstlen) <= dstsize && dstsizecpy)
	{
		dstcpy = dstcpy + dstlen;
		while (*srccpy && dstsizecpy && --dstsizecpy)
			*(dstcpy++) = *(srccpy++);
		*dstcpy = '\0';
	}
	return ((dstsize < dstlen) ? dstsize + srclen : dstlen + srclen);
}
