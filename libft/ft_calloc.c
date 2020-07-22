/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:58:33 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:23:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	unsigned char	*memcpy;
	size_t			totalsize;

	totalsize = count * size;
	if (!(mem = malloc(totalsize)))
		return (NULL);
	memcpy = mem;
	while (totalsize--)
		*(memcpy++) = 0;
	return ((void*)mem);
}
