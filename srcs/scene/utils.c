/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 04:24:31 by badam             #+#    #+#             */
/*   Updated: 2020/07/23 15:18:19 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		scene_defaults(t_scene *scene)
{
	scene->screen_w = 640;
	scene->screen_h = 480;
	scene->fov = FOV;
	scene->ceil.color.red = 50;
	scene->ceil.color.green = 90;
	scene->ceil.color.blue = 235;
	scene->floor.color.red = 50;
	scene->floor.color.green = 50;
	scene->floor.color.blue = 50;
}

static void	create_ceilfloor(t_scene *scene)
{
	t_surface	*surf;

	surf = &(scene->floor_surf);
	surf->texture = &(scene->floor.texture);
	surf->base.u.z = 1;
	surf->base.v.x = 1;
	surf->base.n = cross_product(surf->base.u, surf->base.v);
	surf->o_t.x = 0.5;
	surf->o_t.z = 0.5;
	surf = &(scene->ceil_surf);
	surf->texture = &(scene->ceil.texture);
	surf->base.u.z = 1;
	surf->base.v.x = 1;
	surf->base.n = cross_product(surf->base.u, surf->base.v);
	surf->o_t.y = 1;
	surf->o_t.x = 0.5;
	surf->o_t.z = 0.5;
}

static void	calculate_fov(t_scene *scene)
{
	if (scene->fov > 90)
		scene->fov = 90;
	scene->vfov = scene->fov * (scene->screen_h / (double)scene->screen_w);
	if (scene->vfov > 90)
	{
		scene->vfov = 90;
		scene->fov = scene->vfov / (scene->screen_h / (double)scene->screen_w);
	}
}

bool		validate_scene(t_scene *scene)
{
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
	calculate_fov(scene);
	scene->x_floor = to_x_color(&(scene->floor.color));
	scene->x_ceil = to_x_color(&(scene->ceil.color));
	create_ceilfloor(scene);
	scene->shadow_begin = scene->shadow - scene->shadow_fade;
	scene->state.inventory[ITEM_EMPTY] = true;
	scene->mouse_in = true;
	scene->focused = true;
	return (validate_map(scene));
}
