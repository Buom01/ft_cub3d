/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/06/08 21:55:48 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	draw_frame(const t_scene *sc)
{
	mlx_put_image_to_window(sc->mlx, sc->window, sc->frame, 0, 0);
}

static inline bool	tr_surface(t_ray ray, t_vec n, t_surf_cache cache, 
		int *texture_colors, int *color)
{
	double	rev_n_dot_r; //plan et ray
	double	i_r;
	double	i_u;
	double	i_v;

	rev_n_dot_r = 1.0 / dot_product(n, ray.direction);
	i_r = -cache.n_dot_o_tr * rev_n_dot_r;
	if (i_r < 0)
		return (false);
	i_u = dot_product(cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
	if (i_u < 0 || i_u > 1)
		return (false);
	i_v = dot_product(cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
	if (i_v < 0 || i_v > 1)
		return (false);

	*color = get_texture_color(i_v, i_u, texture_colors);
	
	return (true);
}

static inline void	raytr_tr(const t_scene *sc, int x, int y,
		t_ray ray, const t_surface *surfs)
{
	t_surface	*surf;
	int			color;
	int			*color_p;
	int			*frame_colors;
	int			frame_w;

	color_p = &color;
	frame_colors = sc->frame_colors;
	frame_w = sc->screen_w;
	surf = (t_surface *)surfs;
	while(surf)
	{
		if (tr_surface(ray, surf->base.n, surf->cache, surf->texture->colors,
				color_p))
		{
			set_texture_color(frame_colors, frame_w, x, y, color);
			return;
		}
		surf = surf->next;
	}
	if (ray.direction.y < 0)
		set_texture_color(frame_colors, frame_w, x, y, sc->x_floor);
	else
		set_texture_color(frame_colors, frame_w, x, y, sc->x_ceil);
}

void		raytr_render(const t_scene *sc, const t_vec p_vec)
{
	register int	x;
	register int	y;
	register int	h;
	register int	w;
	register int	fov;
	register int	vfov;
	t_vec			v_vec;
	t_ray			ray;
	t_surface		*optisurfs;

	h = sc->screen_h;
	w = sc->screen_w;
	vfov = sc->vfov;
	fov = sc->fov;
	ray.origin = sc->state.pos;
	raytr_get_surfaces(sc, &optisurfs, ray.origin);
	y = 0;
	while (y < h)
	{
		v_vec = p_vec;
		vec_rel_rot(&v_vec, AXIS_PITCH,
				((double)(y - h * 0.5) / h * PI ) * 0.5  * vfov);
		x = 0;
		while (x < w)
		{
			ray.direction = v_vec;
			vec_rel_rot(&(ray.direction), AXIS_YAW,
					((double)(x - w * 0.5) / w * PI) * 0.5 * fov);
			raytr_tr(sc, x, y, ray, optisurfs);
			++x;
		}
		++y;
	}
	draw_frame(sc);
	raytr_free_surfs(optisurfs);
}
