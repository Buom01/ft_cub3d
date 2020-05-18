/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/05/15 00:15:21 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	tr_surface(t_scene *sc, t_ray *ray, t_surface *surf, t_color *color)
{
	t_vec	tmp;
	t_vec	O_tr;
	double	I_r;
	double	I_u;
	double	I_v;

	// Attention; la base u v r est relative au plan
	O_tr = ;
	I_r = -dot_product(&(sc->base.x), &O_tr);
	if (I_r < 0)
		return (false);
	tmp = cross_product(&O_tr, &(sc->base.y));
	I_u = dot_product(tmp, sc->base.y);
	if (I_u < 0 || I_u > 0)
		return (false);
	tmp = cross_product(&(sc->base.x), &O_tr);
	I_v = dot_product(tmp, sc->base.y);
	if (I_u < 0 || I_u > 0)
		return (false);
	(void)sc;
	(void)vec;
	(void)surf;
	return (true);
}

static void	raytr_tr(t_scene *sc, int x, int y, t_ray *ray, t_surface *surfs)
{
	t_color	color;

	while(surfs)
	{
		if (tr_surface(sc, ray, surfs, &color))
			return;
		surfs = surfs->next;
	}
}

void		raytr_render(t_scene *sc, t_vec p_vec)
{
	int			x;
	int			y;
	t_vec		v_vec;
	t_ray		ray;
	t_surface	*optisurfs;

	x = 0;
	y = 0;
	ray.origin = sc->state.pos;
	raytr_get_surfaces(sc, &optisurfs);
	while (y < sc->screen_h)
	{
		v_vec = p_vec;
		vec_rel_rot(&v_vec, AXIS_PITCH,
				(float)(y - sc->screen_h / 2) / sc->screen_h * sc->vfov);
		while (x < sc->screen_w)
		{
			ray.direction = v_vec;
			vec_rel_rot(&(ray.direction), AXIS_YAW,
					(float)(x - sc->screen_w / 2) / sc->screen_w * sc->fov);
			raytr_tr(sc, x++, y++, &ray, optisurfs);
		}
	}
	raytr_free_surfs(optisurfs);
}
