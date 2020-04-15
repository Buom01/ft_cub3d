/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_physics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 01:13:22 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 02:16:12 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	physics_walkable(t_map *map, size_t pos)
{
	if (pos <= map->width || pos >= map->length - map->width ||
			pos % map->width == 0 || pos % map->width == map->width - 1)
		error(ERR_MAP_UNKNOWN, NULL);
	if (map->walkable[pos])
		return;
	map->walkable[pos] = true;
	if (map->data[pos - map->width] != MAP_WALL)
		physics_walkable(map, pos - map->width);
	if (map->data[pos + map->width] != MAP_WALL)
		physics_walkable(map, pos + map->width);
	if (map->data[pos - 1] != MAP_WALL)
		physics_walkable(map, pos - 1);
	if (map->data[pos + 1] != MAP_WALL)
		physics_walkable(map, pos + 1);
}

void	physics_init(t_map *map)
{
	size_t	pos;

	if (!(map->walkable = malloc(map->length * sizeof(bool))))
		error(ERR_MAP_MALLOC, NULL);
	ft_memset(map->walkable, 0, map->length * sizeof(bool));
	pos = map_get_player_pos(map);
	physics_walkable(map, pos);
}
