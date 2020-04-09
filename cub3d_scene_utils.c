/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 04:24:31 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 05:06:44 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_defaults(t_scene *scene)
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

bool	validate_scene(t_scene *scene)
{
	if (!(scene->map.data && scene->north && scene->south && scene->west
			&& scene->east && scene->sprite))
		return false;
	if (scene->screen_w <= 0 && scene->screen_h <= 0)
		error(ERR_INV_CONFIG, "R");
	if (ft_strlen(scene->north) == 0)
		error(ERR_INV_CONFIG, "NO");
	if (ft_strlen(scene->south) == 0)
		error(ERR_INV_CONFIG, "SO");
	if (ft_strlen(scene->west) == 0)
		error(ERR_INV_CONFIG, "WE");
	if (ft_strlen(scene->east) == 0)
		error(ERR_INV_CONFIG, "EA");
	if (ft_strlen(scene->sprite) == 0)
		error(ERR_INV_CONFIG, "S");
	return true;
}

