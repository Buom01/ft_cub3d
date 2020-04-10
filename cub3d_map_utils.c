/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:08:39 by badam             #+#    #+#             */
/*   Updated: 2020/04/10 23:13:16 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t  		map_find_longer_line(char **rawmap)
{
	size_t	longer;
	size_t	length;

	longer = 0;
	while (*rawmap)
	{
		length = ft_strlen(*rawmap);
		if (length > longer)
			longer = length;
		rawmap++;
	}
	return (longer);
}

size_t  		map_find_textblock_height(char **rawmap)
{
	size_t	height;

	height = 0;
	while ( *(*rawmap + height) )
		height++;
	return (height);
}

