/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:07:12 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 21:36:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_surface(t_texture *textr, t_pos pos, t_angle yaw,
		t_surface **rst, t_surface **lst)
{
	t_surface	*surf;

	if (!(surf = malloc(sizeof(t_surface))))
		error(ERR_MAP_MALLOC, NULL);
	ft_memset(surf, 0, sizeof(t_surface));
	surf->pos = pos;
	surf->yaw = yaw;
	surf->texture = textr;
	if (!(*rst))
		*rst = surf;
	else
		(*lst)->next = surf;
	*lst = surf;
}

static void	add_surfaces(t_map *map, size_t i, t_scene *scene,
	t_surface **rst, t_surface **lst)
{
	if (!map->walkable[i])
		return;
	if (map->data[i - map->width] == MAP_WALL)
		add_surface(&scene->north, i2pos(map, i, DIR_NORTH), 180, rst, lst);
	if (map->data[i + map->width] == MAP_WALL)
		add_surface(&scene->south, i2pos(map, i, DIR_SOUTH), 0, rst, lst);
	if (map->data[i - 1] == MAP_WALL)
		add_surface(&scene->west, i2pos(map, i, DIR_WEST), -90, rst, lst);
	if (map->data[i + 1] == MAP_WALL)
		add_surface(&scene->east, i2pos(map, i, DIR_EAST), 90, rst, lst);
}

void		raytr_init(t_scene *scene)
{
	size_t 		i;
	t_map		*map;
	t_surface	*lstsurf;

	i = 0;
	lstsurf = scene->surfaces;
	map = &scene->map;
	while (i < map->length)
		add_surfaces(map, i++, scene, &scene->surfaces, &lstsurf);
}
