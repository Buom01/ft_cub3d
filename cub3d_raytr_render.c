/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 23:31:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	draw_frame(const t_scene *sc)
{
	mlx_put_image_to_window(sc->mlx, sc->window, sc->frame, 0, 0);
}

static inline bool	tr_surface(t_ray ray, t_vec n, t_surf_cache cache, 
		const int *texture_colors, int *color)
{
	double	rev_n_dot_r;
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
	*color = get_texture_color_at(i_v, i_u, texture_colors);
	return (true);
}

static inline void	raytr_tr(const t_scene *sc, int pixel_index,
		t_ray ray, t_surface *surfs)
{
	t_surface	*surf;
	int			*pixel;

	pixel = sc->frame_colors + pixel_index;
	surf = (t_surface *)surfs;
	while (surf)
	{
		if (tr_surface(ray, surf->base.n, surf->cache,
						surf->texture->colors, pixel))
			return;
		surf = surf->next;
	}
	if (ray.direction.y < 0)
		*pixel = sc->x_floor;
	else
		*pixel = sc->x_ceil;
}

inline void			raytr_render(const t_scene *sc, const t_state *state,
		int w, int h)
{
	register int	x;
	register int	y;
	t_ray			ray;
	t_surface		*optisurfs;
	t_vec			*direction_p;
	int				pixel_index;

	ray.origin = state->pos;
	direction_p = &(ray.direction);
	raytr_get_surfaces(sc, &optisurfs, ray.origin);
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
			raytr_tr(sc, pixel_index, ray, optisurfs);
			++pixel_index;
			++x;
		}
		++y;
	}
	draw_frame(sc);
	raytr_free_surfs(optisurfs);
}
