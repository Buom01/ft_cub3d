/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:21:00 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 22:37:00 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_surface(t_surface *surf,
		t_pos pos, t_angle yaw, t_texture *texture)
{
	surf->pos = pos;
	surf->yaw = yaw;
	surf->texture = texture;
}

static void	add_wall_block(t_scene *sc, size_t i,
		t_map *map, t_surface **lst)
{
	t_surface	*surf;

	if (!map->walkable[i])
		return ;
	if (map->data[i - map->width] == MAP_WALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_NORTH), PI, &(sc->north));
	}
	if (map->data[i + map->width] == MAP_WALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_SOUTH), 0, &(sc->south));
	}
	if (map->data[i - 1] == MAP_WALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_WEST), PI / 2, &(sc->west));
	}
	if (map->data[i + 1] == MAP_WALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_EAST), PI * 3 / 2, &(sc->east));
	}
}

void		walls_init(t_scene *scene, t_map *map)
{
	size_t		i;
	t_surface	*surf;

	i = 0;
	surf = scene->surfaces;
	while (i < map->length)
		add_wall_block(scene, i++, map, &surf);
	surf = scene->surfaces;
	while (surf)
	{
		update_surface(surf);
		surf = surf->next;
	}
}

void		walls_update(t_scene *sc, t_ray ray,
		t_surface **lst_surf, t_surface **surfs)
{
	t_surface	*candidate;

	candidate = sc->surfaces;
	while (candidate)
	{
		if (is_surface_useful(candidate, ray, sc->state.yaw, sc))
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

void		walls_shutdown(t_scene *scene)
{
	free_surfaces(scene->surfaces);
	scene->surfaces = NULL;
}
