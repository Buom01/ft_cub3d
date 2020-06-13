/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:07:12 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 22:37:00 by badam            ###   ########.fr       */
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
		add_surface(&scene->west, i2pos(map, i, DIR_WEST), 90, rst, lst);
	if (map->data[i + 1] == MAP_WALL)
		add_surface(&scene->east, i2pos(map, i, DIR_EAST), 270, rst, lst);
}

static void	init_static_surfaces(t_scene *scene)
{
	t_surface *surfs;

	surfs = scene->surfaces;
	while (surfs)
	{
		update_surface(surfs);
		surfs = surfs->next;
	}

}

static void	generate_view_matrix(t_scene *scene, int w, int h,
		double fov, double vfov)
{
	int		i;
	double	min;
	double	to_max;
	double	screen_w;
	double	screen_h;

	screen_w = tan(fov * TORAD / 2) * 2;
	screen_h = tan(vfov * TORAD / 2) * 2;
	if ( !(scene->x2yaw = malloc(sizeof(double) * w)) )
		error(ERR_MAP_MALLOC, NULL);
	if ( !(scene->y2pitch = malloc(sizeof(double) * h)) )
		error(ERR_MAP_MALLOC, NULL);
	min = -screen_w / 2;
	to_max = screen_w;
	i = 0;
	while (i < w)
	{
		scene->x2yaw[i] = atan(min + to_max * i / w) * TODEG;
		++i;
	}
	min = -screen_h / 2;
	to_max = screen_h;
	i = 0;
	while (i < h)
	{
		scene->y2pitch[i] = atan(min + to_max * i / h) * TODEG;
		++i;
	}
}

void		raytr_init(t_scene *sc)
{
	size_t 		i;
	t_map		*map;
	t_surface	*lstsurf;

	i = 0;
	lstsurf = sc->surfaces;
	map = &sc->map;
	while (i < map->length)
		add_surfaces(map, i++, sc, &(sc->surfaces), &lstsurf);
	init_static_surfaces(sc);
	generate_view_matrix(sc, sc->screen_w, sc->screen_h, sc->fov, sc->vfov);
}
