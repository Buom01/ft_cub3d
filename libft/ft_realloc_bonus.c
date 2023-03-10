/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:55:29 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 03:19:52 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t dstsize, size_t srcsize)
{
	void	*ptr2;

	if (dstsize)
	{
		if (!(ptr2 = malloc(dstsize)))
			return (NULL);
		if (ptr)
			ft_memcpy(ptr2, ptr, (srcsize <= dstsize ? srcsize : dstsize));
	}
	else
		ptr2 = NULL;
	if (ptr)
		free(ptr);
	return (ptr2);
}
