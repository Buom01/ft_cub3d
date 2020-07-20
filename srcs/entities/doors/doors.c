/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:03:26 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 23:46:57 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	door_pre_update(t_scene *sc, t_door *candidate)
{
	if (candidate->key == ITEM_EMPTY)
	{
		if (dist_2d(sc->state.pos, candidate->pos) < 2.25)
			candidate->state += 0.01;
		else
			candidate->state -= 0.01;
	}
	else if (sc->state.inventory[candidate->key])
		candidate->state += 0.01;
	sc->map.walkable[candidate->physic_index] =
		((candidate->state = born(candidate->state, 0.0, 1.0)) > 0.85);
}

void		doors_update(t_scene *sc, t_ray ray, t_surface **lst_surf)
{
	t_door		*candidate;

	candidate = sc->doors;
	while (candidate)
	{
		door_pre_update(sc, candidate);
		if (candidate->type == DOOR_STANDARD)
			door_standard_update(candidate, ray, sc, lst_surf);
		else if (candidate->type == DOOR_GRID)
			door_grid_update(candidate, ray, sc, lst_surf);
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
