/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:38:59 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 23:39:21 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_door(t_entity ent)
{
	return (ent == MAP_DOOR || ent == MAP_DOOR_GRID);
}

static void	init_door_from_type(t_door *door, size_t i, t_map *map, t_scene *sc)
{
	t_entity	ent;

	ent = map->data[i];
	door->vertical = !(map->data[i + 1] == MAP_WALL
			&& map->data[i - 1] == MAP_WALL);
	if (ent == MAP_DOOR)
	{
		door->type = DOOR_STANDARD;
		door->texture = &(sc->door_a);
		door->texture_b = &(sc->door_b);
	}
	else if (ent == MAP_DOOR_GRID)
	{
		door->type = DOOR_GRID;
		door->texture = &(sc->door_grid);
		door->key = ITEM_KEY;
	}
}

void		doors_init(t_scene *scene, t_map *map)
{
	size_t	i;
	t_door	*door;
	t_door	*lst;

	lst = NULL;
	i = 0;
	while (i < map->length)
	{
		if (is_door(map->data[i]))
		{
			if (!(door = malloc(sizeof(t_door))))
				error(scene, ERR_MALLOC, NULL);
			ft_memset(door, 0, sizeof(t_door));
			init_door_from_type(door, i, map, scene);
			door->pos = i2pos(map, i, DIR_NONE);
			door->physic_index = i;
			if (!(scene->doors))
				scene->doors = door;
			if (lst)
				lst->next = door;
			lst = door;
		}
		++i;
	}
}
