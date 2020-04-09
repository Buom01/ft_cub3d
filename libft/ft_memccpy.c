/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:44:54 by badam             #+#    #+#             */
/*   Updated: 2019/11/12 20:46:01 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "ft_strlen.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*srccpy;
	unsigned char	*srccpybgn;
	unsigned char	*dstcpy;
	unsigned char	ccpy;

	dstcpy = (unsigned char*)dst;
	srccpy = (unsigned char*)src;
	srccpybgn = (unsigned char*)src;
	ccpy = (unsigned char)c;
	while (n-- && (srccpy == srccpybgn || *(srccpy - 1) != ccpy))
		*(dstcpy++) = *(srccpy++);
	return ((srccpy != srccpybgn && *(srccpy - 1) == ccpy) ?
				(void*)(dstcpy) : NULL);
}
