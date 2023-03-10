/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:58:54 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:18:47 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	ssize_t	rslt;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len)
		rslt = write(fd, (const void*)s, len);
	(void)rslt;
}
