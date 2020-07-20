/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fakewalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:21:00 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 23:26:13 by badam            ###   ########.fr       */
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

static void	add_fakewall_block(t_scene *sc, size_t i,
		t_map *map, t_surface **lst)
{
	t_surface	*surf;

	if (!map->walkable[i] || map->data[i] == MAP_FAKEWALL)
		return ;
	if (map->data[i - map->width] == MAP_FAKEWALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_NORTH), 180, &(sc->north));
	}
	if (map->data[i + map->width] == MAP_FAKEWALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_SOUTH), 0, &(sc->south));
	}
	if (map->data[i - 1] == MAP_FAKEWALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_WEST), 90, &(sc->west));
	}
	if (map->data[i + 1] == MAP_FAKEWALL)
	{
		surf = add_surface(&(sc->surfaces), lst, sc);
		set_surface(surf, i2pos(map, i, DIR_EAST), 270, &(sc->east));
	}
}

void		fakewalls_init(t_scene *scene, t_map *map)
{
	size_t		i;
	t_surface	*begin_new_surf;
	t_surface	*surf;

	i = 0;
	surf = scene->surfaces;
	while (surf->next)
		surf = surf->next;
	begin_new_surf = surf;
	while (i < map->length)
		add_fakewall_block(scene, i++, map, &surf);
	surf = begin_new_surf;
	while (surf)
	{
		update_surface(surf);
		surf = surf->next;
	}
}
