/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:40:12 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 02:28:22 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	scene_defaults(t_scene *scene)
{
	scene->screen_w = 640;
	scene->screen_h = 480;
	scene->ceil[0] = 50;
	scene->ceil[1] = 90;
	scene->ceil[2] = 235;
	scene->floor[0] = 50;
	scene->floor[1] = 50;
	scene->floor[2] = 50;
}

static bool	scene_has_minimum(t_scene *scene)
{
	return (scene->map.data && scene->north && scene->south && scene->west
			&& scene->east && scene->sprite);
}

static void	parse_line(char	*line)
{
	(void)line;
}

int			parse_scene(char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl_result;

	scene_defaults(scene);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (error(ERR_OPENING_SCENE, path));
	while ((gnl_result = get_next_line(fd, &line)) == 1)
	{
		parse_line(line);
		free(line);
	}
	close(fd);
	if (gnl_result == -1)
		return (error(ERR_READING_SCENE, path));
	scene->loaded = scene_has_minimum(scene);
	return (0);
}
