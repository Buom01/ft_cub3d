/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:02:00 by badam             #+#    #+#             */
/*   Updated: 2020/07/07 17:50:27 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline bool	is_walkable(double x, double z, const t_scene *scene)
{
	t_pos		pos;
	long long	ipos;

	pos = scene->state.pos;
	pos.x += x;
	pos.z += z;
	ipos = pos2i(&(scene->map), pos);
	return (ipos != -1 && scene->map.walkable[ipos]);
}

static inline bool	can_move(double x, double z, const t_scene *scene)
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

static inline void	physics_major_move(double *x, double *z,
		const t_scene *scene)
{
	double			simulate_x;
	double			simulate_z;

	if (*x > 1)
		*x = 1;
	if (*z > 1)
		*z = 1;
	simulate_x = *x + sign(*x) * PLAYER_RADIUS;
	simulate_z = *z + sign(*z) * PLAYER_RADIUS;
	if (can_move(simulate_x, 0, scene))
	{
		if (!can_move(0, simulate_z, scene))
			*z = 0;
	}
	else if (can_move(0, simulate_z, scene))
	{
		if (!can_move(simulate_x, 0, scene))
			*x = 0;
	}
	else if (!can_move(simulate_x, simulate_z, scene))
	{
		*x = 0;
		*z = 0;
	}
}

void				physics_apply(t_scene *scene)
{
	physics_major_move(&(scene->state.move_x), &(scene->state.move_z), scene);
	scene->state.pos.x += scene->state.move_x;
	scene->state.pos.z += scene->state.move_z;
	scene->state.move_x = 0;
	scene->state.move_z = 0;
}
