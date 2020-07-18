/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:03:26 by badam             #+#    #+#             */
/*   Updated: 2020/07/18 14:35:05 by badam            ###   ########.fr       */
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

void		doors_init(t_scene *scene)
{
	size_t	i;
	t_map	*map;
	t_door	*door;
	t_door	*lst;

	map = &(scene->map);
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

void		doors_update(t_scene *sc, t_ray ray, t_surface **lst_surf)
{
	t_door		*candidate;

	candidate = sc->doors;
	while (candidate)
	{
		if (candidate->type == DOOR_STANDARD)
			door_standard_update(candidate, ray, sc, lst_surf);
		candidate = candidate->next;
	}
	if (*lst_surf)
		(*lst_surf)->next = NULL;
}

void		doors_shutdown(t_scene *scene)
{
	t_door	*door;
	t_door	*next;

	door = scene->doors;
	while (door)
	{
		next = door->next;
		free(door);
		door = next;
	}
	scene->doors = NULL;
}
