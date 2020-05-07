/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/04/30 15:52:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	tr_surface(t_scene *sc, int x, int y, t_vec vec, t_surface *surf)
{
	(void)sc;
	(void)x;
	(void)y;
	(void)vec;
	(void)surf;
	return (true);
}

static void	raytr_tr(t_scene *sc, int x, int y, t_vec vec, t_surface *surfs)
{
	while(surfs)
	{
		if (tr_surface(sc, x, y, vec, surfs))
			return;
		surfs = surfs->next;
	}
}

void		raytr_render(t_scene *sc, t_vec p_vec)
{
	int			x;
	int			y;
	t_vec		v_vec;
	t_vec		h_vec;
	t_surface	*optisurfs;

	x = 0;
	y = 0;
	raytr_get_surfaces(sc, &optisurfs);
	while (y < sc->screen_h)
	{
		v_vec = p_vec;
		vec_rel_rot(&v_vec, AXIS_PITCH,
				(float)(y - sc->screen_h / 2) / sc->screen_h * sc->vfov);
		while (x < sc->screen_w)
		{
			h_vec = v_vec;
			vec_rel_rot(&h_vec, AXIS_YAW,
					(float)(x - sc->screen_w / 2) / sc->screen_w * sc->fov);
			raytr_tr(sc, x++, y++, h_vec, optisurfs);
		}
	}
	raytr_free_surfs(optisurfs);
}
