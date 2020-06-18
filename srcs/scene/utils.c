/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 04:24:31 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:36:54 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_defaults(t_scene *scene)
{
	scene->screen_w = 640;
	scene->screen_h = 480;
	scene->fov = FOV;
	scene->ceil.red = 50;
	scene->ceil.green = 90;
	scene->ceil.blue = 235;
	scene->floor.red = 50;
	scene->floor.green = 50;
	scene->floor.blue = 50;
}

bool	validate_scene(t_scene *scene)
{
	if (scene->screen_w <= 0 || scene->screen_h <= 0)
		error(scene, ERR_INV_CONFIG, "R");
	if (!scene->north.path || ft_strlen(scene->north.path) == 0)
		error(scene, ERR_INV_CONFIG, "NO");
	if (!scene->south.path || ft_strlen(scene->south.path) == 0)
		error(scene, ERR_INV_CONFIG, "SO");
	if (!scene->west.path || ft_strlen(scene->west.path) == 0)
		error(scene, ERR_INV_CONFIG, "WE");
	if (!scene->east.path || ft_strlen(scene->east.path) == 0)
		error(scene, ERR_INV_CONFIG, "EA");
	if (!scene->sprite.path || ft_strlen(scene->sprite.path) == 0)
		error(scene, ERR_INV_CONFIG, "S");
	if (scene->fov > 180)
		scene->fov = 180;
	scene->vfov = scene->fov * (scene->screen_h / (double)scene->screen_w);
	scene->x_floor = to_x_color(&(scene->floor));
	scene->x_ceil = to_x_color(&(scene->ceil));
	return (validate_map(scene));
}
