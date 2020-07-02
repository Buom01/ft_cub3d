/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:07:12 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 12:53:23 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	generate_view_matrix(t_scene *scene, int w, int h,
		double fov, double vfov)
{
	int		i;
	double	min;
	double	to_max;
	double	screen_w;
	double	screen_h;

	screen_w = tan(fov * TORAD / 2) * 2;
	screen_h = tan(vfov * TORAD / 2) * 2;
	if ( !(scene->x2yaw = malloc(sizeof(double) * w)) )
		error(scene, ERR_MALLOC, NULL);
	if ( !(scene->y2pitch = malloc(sizeof(double) * h)) )
		error(scene, ERR_MALLOC, NULL);
	min = -screen_w / 2;
	to_max = screen_w;
	i = 0;
	while (i < w)
	{
		scene->x2yaw[i] = atan(min + to_max * i / w) * TODEG;
		++i;
	}
	min = -screen_h / 2;
	to_max = screen_h;
	i = 0;
	while (i < h)
	{
		scene->y2pitch[i] = atan(min + to_max * i / h) * TODEG;
		++i;
	}
}

void		raytr_init(t_scene *sc)
{
	generate_view_matrix(sc, sc->screen_w, sc->screen_h, sc->fov, sc->vfov);
}
