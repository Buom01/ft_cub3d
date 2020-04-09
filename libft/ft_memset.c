/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:45:22 by badam             #+#    #+#             */
/*   Updated: 2019/11/10 19:45:14 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bcpy;

	bcpy = (unsigned char*)b;
	while (len--)
		*(bcpy++) = (unsigned char)c;
	return (b);
}
