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

char	*relative_to(const char *file_from, const char *file)
{
	size_t	last_slash;
	char	*prefix_path;
	char	*complete_path;

	last_slash = ft_strlen(file_from);
	while (last_slash && file_from[last_slash] != '/')
		last_slash--;
	if ( !(prefix_path = ft_strdup(file_from)) )
		error(ERR_MALLOC, NULL);
	prefix_path[last_slash + 1] = '\0';
	if ( !(complete_path = ft_strjoin(prefix_path, file)) )
		error(ERR_MALLOC, NULL);
	free(prefix_path);
	return (complete_path);
}

bool	has_extension(char *path, char *ext)
{
	char	*pathend;

	pathend = path + ft_strlen(path) - ft_strlen(ext);
	if (pathend < path)
		return (false);
	return (!(ft_strcmp(pathend, ext)));
}
