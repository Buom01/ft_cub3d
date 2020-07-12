/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:42:38 by badam             #+#    #+#             */
/*   Updated: 2020/07/09 01:20:47 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_walkable(double x, double z, const t_scene *scene)
{
	t_pos		pos;
	long long	ipos;

	pos = scene->state.pos;
	pos.x += x;
	pos.z += z;
	ipos = pos2i(&(scene->map), pos);
	return (ipos != -1 && scene->map.walkable[ipos]);
}

bool		physics_can_move(double x, double z, const t_scene *scene)
{
	if (x == 0)
	{
		return (is_walkable(-PLAYER_RADIUS, z, scene)
				&& is_walkable(PLAYER_RADIUS, z, scene));
	}
	else if (z == 0)
	{
		return (is_walkable(x, -PLAYER_RADIUS, scene)
				&& is_walkable(x, PLAYER_RADIUS, scene));
	}
	else
		return (is_walkable(x, z, scene));
}

double		physics_get_closest_move(double axis)
{
	double	player_radius;
	double	new_pos;

	player_radius = sign(fmod(axis, 1) - 0.5) * (PLAYER_RADIUS + EPSYLON);
	new_pos = ceil(axis) - 0.5 + player_radius;
	return (new_pos - axis);
}
