/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 01:13:22 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:51:53 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static void	physics_walkable_tree(t_map *map, size_t pos, t_scene *sc)
{
	if (pos <= map->width || pos >= map->length - map->width ||
			pos % map->width == 0 || pos % map->width == map->width - 1)
		error(sc, ERR_MAP_UNKNOWN, NULL);
	if (map->walkable[pos])
		return;
	map->walkable[pos] = true;
	if (map->data[pos - map->width] != MAP_WALL)
		physics_walkable_tree(map, pos - map->width, sc);
	if (map->data[pos + map->width] != MAP_WALL)
		physics_walkable_tree(map, pos + map->width, sc);
	if (map->data[pos - 1] != MAP_WALL)
		physics_walkable_tree(map, pos - 1, sc);
	if (map->data[pos + 1] != MAP_WALL)
		physics_walkable_tree(map, pos + 1, sc);
}

void				physics_init(t_map *map, t_scene *scene)
{
	if (!(map->walkable = malloc(map->length * sizeof(bool))))
		error(scene, ERR_MALLOC, NULL);
	ft_memset(map->walkable, 0, map->length * sizeof(bool));
	physics_walkable_tree(map, map->init_player_pos, scene);
}

void				physics_shutdown(t_map *map)
{
	if (map->walkable)
		free(map->walkable);
}
