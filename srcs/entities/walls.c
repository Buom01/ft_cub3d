/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:21:00 by badam             #+#    #+#             */
/*   Updated: 2020/06/19 13:44:27 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_wall_block(t_map *map, size_t i, t_scene *sc,
	t_surface **rst, t_surface **lst)
{
	if (!map->walkable[i])
		return;
	if (map->data[i - map->width] == MAP_WALL)
		add_surface(&(sc->north), i2pos(map, i, DIR_NORTH), 180, rst, lst, sc);
	if (map->data[i + map->width] == MAP_WALL)
		add_surface(&(sc->south), i2pos(map, i, DIR_SOUTH), 0, rst, lst, sc);
	if (map->data[i - 1] == MAP_WALL)
		add_surface(&(sc->west), i2pos(map, i, DIR_WEST), 90, rst, lst, sc);
	if (map->data[i + 1] == MAP_WALL)
		add_surface(&(sc->east), i2pos(map, i, DIR_EAST), 270, rst, lst, sc);
}

void		walls_init(t_scene *scene)
{
	size_t 		i;
	t_map		*map;
	t_surface	*surf;

	i = 0;
	surf = scene->surfaces;
	map = &(scene->map);
	while (i < map->length)
		add_wall_block(map, i++, scene, &(scene->surfaces), &surf);
	surf = scene->surfaces;
	while (surf)
	{
		update_surface(surf);
		surf = surf->next;
	}
}

inline void	walls_update(t_scene *sc, t_state *state, t_ray ray,
		t_surface **lst_surf, t_surface **surfs)
{
	t_surface	*candidate;

	candidate = sc->surfaces;
	while (candidate)
	{
		if (is_surface_useful(candidate, ray, state->yaw))
		{
			add_render_surface(candidate, lst_surf, sc);
			if (!(*surfs))
				*surfs = *lst_surf;
		}
		candidate = candidate->next;
	}
	if (*lst_surf)
		(*lst_surf)->next = NULL;
}

void	walls_shutdown(t_scene *scene)
{
	free_surfaces(scene->surfaces);
	scene->surfaces = NULL;
}
