/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceilfloor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:07:38 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 23:09:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tr_floor(t_ray ray, int *color, const t_scene *sc)
{
	const t_surface	*fl;
	double			rev_n_dot_r;
	double			i_r;
	double			i_u;
	double			i_v;

	i_r = 0;
	if (!sc->floor.is_texture)
		*color = sc->x_floor;
	if (sc->shadow || sc->floor.is_texture)
	{
		fl = &(sc->floor_surf);
		rev_n_dot_r = 1 / dot_product(fl->base.n, ray.direction);
		i_r = -(fl->cache.n_dot_o_tr) * rev_n_dot_r;
	}
	if (sc->floor.is_texture && (!sc->shadow || sc->shadow > i_r))
	{
		i_u = dot_product(fl->cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
		i_v = dot_product(fl->cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
		*color = get_texture_color_at(fmod(i_v, 1), fmod(i_u, 1),
				fl->texture, NULL);
	}
	tr_correctify_color(color, i_r, sc);
}

void	tr_ceil(t_ray ray, int *color, const t_scene *sc)
{
	const t_surface	*cl;
	double			rev_n_dot_r;
	double			i_r;
	double			i_u;
	double			i_v;

	i_r = 0;
	if (!sc->ceil.is_texture)
		*color = sc->x_ceil;
	if (sc->shadow || sc->ceil.is_texture)
	{
		cl = &(sc->ceil_surf);
		rev_n_dot_r = 1 / dot_product(cl->base.n, ray.direction);
		i_r = -(cl->cache.n_dot_o_tr) * rev_n_dot_r;
	}
	if (sc->ceil.is_texture && (!sc->shadow || sc->shadow > i_r))
	{
		i_u = dot_product(cl->cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
		i_v = dot_product(cl->cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
		*color = get_texture_color_at(fmod(i_v, 1), fmod(i_u, 1),
				cl->texture, NULL);
	}
	tr_correctify_color(color, i_r, sc);
}
