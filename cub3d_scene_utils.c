/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 04:24:31 by badam             #+#    #+#             */
/*   Updated: 2020/04/20 18:04:13 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_defaults(t_scene *scene)
{
	scene->screen_w = 640;
	scene->screen_h = 480;
	scene->fov = FOV;
	scene->ceil[0] = 50;
	scene->ceil[1] = 90;
	scene->ceil[2] = 235;
	scene->floor[0] = 50;
	scene->floor[1] = 50;
	scene->floor[2] = 50;
}

bool	validate_scene(t_scene *scene)
{
	if (scene->screen_w <= 0 && scene->screen_h <= 0)
		error(ERR_INV_CONFIG, "R");
	if (!scene->north.path || ft_strlen(scene->north.path) == 0)
		error(ERR_INV_CONFIG, "NO");
	if (!scene->south.path || ft_strlen(scene->south.path) == 0)
		error(ERR_INV_CONFIG, "SO");
	if (!scene->west.path || ft_strlen(scene->west.path) == 0)
		error(ERR_INV_CONFIG, "WE");
	if (!scene->east.path || ft_strlen(scene->east.path) == 0)
		error(ERR_INV_CONFIG, "EA");
	if (!scene->sprite.path || ft_strlen(scene->sprite.path) == 0)
		error(ERR_INV_CONFIG, "S");
	scene->vfov = scene->fov * (float)scene->screen_w / (float)scene->screen_h;
	return (validate_map(scene));
}
