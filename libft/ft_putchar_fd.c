/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:52:08 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:30:35 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	buf[1];
	ssize_t			rslt;

	*buf = (unsigned char)c;
	rslt = write(fd, (const void*)buf, 1);
	(void)rslt;
}
