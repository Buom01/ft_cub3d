/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:23:37 by badam             #+#    #+#             */
/*   Updated: 2020/04/11 00:54:02 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_extension(char *path, char *ext)
{
	char	*pathend;

	pathend = path + ft_strlen(path) - ft_strlen(ext);
	if (pathend < path)
		return (false);
	return (!(ft_strcmp(pathend, ext)));
}
