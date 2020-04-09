/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:52:08 by badam             #+#    #+#             */
/*   Updated: 2019/11/05 19:54:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	buf[1];

	*buf = (unsigned char)c;
	write(fd, (const void*)buf, 1);
}
