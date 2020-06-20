/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/06/20 17:27:08 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	draw_frame(const t_scene *sc)
{
	mlx_put_image_to_window(sc->mlx, sc->window, sc->frame, 0, 0);
}

static inline int	tr_surface(t_ray ray, t_vec n, t_surf_cache cache, 
		const int *texture_colors, int *color)
{
	double	rev_n_dot_r;
	double	i_r;
	double	i_u;
	double	i_v;

	if (fabs(ray.direction.y * cache.distance) > 1)
		return (TR_FLOOR); 

	rev_n_dot_r = 1.0 / dot_product(n, ray.direction);
	if (rev_n_dot_r > 0)
		return (TR_NOT_HIT);
	i_r = -cache.n_dot_o_tr * rev_n_dot_r;
	if (i_r < 0)
		return (TR_NOT_HIT);
	i_u = dot_product(cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
	if (i_u < 0 || i_u > 1)
		return (TR_NOT_HIT);
	i_v = dot_product(cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
	if (i_v < 0 || i_v > 1)
		return (TR_NOT_HIT);
	*color = get_texture_color_at(i_v, i_u, texture_colors);
	if ((unsigned char)(*color >> 24) > 127)
		return (TR_NOT_HIT);
	if (MAX_DIST)
		color_darken(color, (i_r - MAX_DIST + SHADOW_DIST) / SHADOW_DIST);
	return (TR_HIT);
}

static inline void	raytr_tr(const t_scene *sc, int pixel_index,
		t_ray ray, t_surface *surfs)
{
	int			tr_result;
	t_surface	*surf;
	int			*pixel;

	pixel = sc->frame_colors + pixel_index;
	surf = (t_surface *)surfs;
	while (surf)
	{
		tr_result = tr_surface(ray, surf->base.n, surf->cache,
				surf->texture->colors, pixel);
		if (tr_result == TR_HIT)
			return;
		else if (tr_result == TR_FLOOR)
			surf = NULL;
		else
			surf = surf->next;
	}
	if (ray.direction.y < 0)
		*pixel = sc->x_floor;
	else
		*pixel = sc->x_ceil;
}

inline void			raytr_render(t_scene *sc, t_surface **surfs,
		t_ray ray, int w, int h)
{
	t_state			*state;
	register int	x;
	register int	y;
	t_vec			*direction_p;
	int				pixel_index;

	state = &(sc->state);
	direction_p = &(ray.direction);
	surfaces_sort(surfs);
	surfaces_pre_tr(*surfs, ray.origin);
	pixel_index = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			vec_from_angles(
				direction_p,
				sc->x2yaw[x] + state->yaw,
				sc->y2pitch[y] + state->pitch
			);
			raytr_tr(sc, pixel_index, ray, *surfs);
			++pixel_index;
			++x;
		}
		++y;
	}
	draw_frame(sc);
}
