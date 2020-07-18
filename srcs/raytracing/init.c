/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:07:12 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 23:15:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	generate_view_matrix(t_scene *scene, int w, int h)
{
	int		i;
	double	min;
	double	screen_w;
	double	screen_h;

	screen_w = tan(scene->fov * TORAD / 2) * 2;
	screen_h = tan(scene->vfov * TORAD / 2) * 2;
	if (!(scene->x2yaw = malloc(sizeof(double) * w)))
		error(scene, ERR_MALLOC, NULL);
	if (!(scene->y2pitch = malloc(sizeof(double) * h)))
		error(scene, ERR_MALLOC, NULL);
	min = -screen_w / 2;
	i = 0;
	while (i < w)
	{
		scene->x2yaw[i] = atan(min + screen_w * i / w) * TODEG;
		++i;
	}
	min = -screen_h / 2;
	i = 0;
	while (i < h)
	{
		scene->y2pitch[i] = atan(min + screen_h * i / h) * TODEG;
		++i;
	}
}

void		raytr_init(t_scene *sc)
{
	generate_view_matrix(sc, sc->screen_w, sc->screen_h);
}
