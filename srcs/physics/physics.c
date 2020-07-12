/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:02:00 by badam             #+#    #+#             */
/*   Updated: 2020/07/11 04:20:48 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	move_back(double sim_x, double sim_z, const t_scene *sc)
{
	if (sim_z == 0)
		return (physics_get_closest_move(sc->state.pos.x));
	else if (sim_x == 0)
		return (physics_get_closest_move(sc->state.pos.z));
	else
		return (0);
}

static void		solve_corner(double *x, double *z, double back_x, double back_z)
{
	if (fabs(back_x) < fabs(back_z))
		*z = back_z;
	else
		*x = back_x;
}

static void		major_move(double *x, double *z, const t_scene *scene)
{
	double	sim_x;
	double	sim_z;

	sim_x = *x + sign(*x) * PLAYER_RADIUS;
	sim_z = *z + sign(*z) * PLAYER_RADIUS;
	if (physics_can_move(sim_x, 0, scene))
	{
		if (!physics_can_move(0, sim_z, scene))
			*z = move_back(0, sim_z, scene);
		else if (!physics_can_move(sim_x, sim_z, scene))
			solve_corner(x, z,
				move_back(sim_x, 0, scene), move_back(0, sim_z, scene));
	}
	else if (physics_can_move(0, sim_z, scene))
	{
		if (!physics_can_move(sim_x, 0, scene))
			*x = move_back(sim_x, 0, scene);
	}
	else
	{
		*x = move_back(sim_x, 0, scene);
		*z = move_back(0, sim_z, scene);
	}
}

void			physics_apply(t_scene *scene)
{
	if (!(scene->noclip))
		major_move(&(scene->state.move_x), &(scene->state.move_z), scene);
	scene->state.pos.x += scene->state.move_x;
	scene->state.pos.z += scene->state.move_z;
	scene->state.move_x = 0;
	scene->state.move_z = 0;
}
