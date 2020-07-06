/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/07/06 19:00:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				draw_frame(const t_scene *sc)
{
	mlx_put_image_to_window(sc->mlx, sc->window, sc->frame, 0, 0);
}

static inline int	tr_surface(t_ray ray, t_surface *surf, int *color,
		const t_scene *sc)
{
	double	n_dot_r;
	double	rev_n_dot_r;
	double	i_r;
	double	i_u;
	double	i_v;

	if (fabs(ray.direction.y * surf->cache.distance) > 1)
		return (TR_FLOOR);
	n_dot_r = dot_product(surf->base.n, ray.direction);
	rev_n_dot_r = 1 / n_dot_r;
	if (n_dot_r > 0)
		return (TR_NOT_HIT);
	i_r = -(surf->cache.n_dot_o_tr) * n_dot_r;
	if (i_r < 0)
		return (TR_NOT_HIT);
	i_u = dot_product(surf->cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
	if (i_u < 0 || i_u > 1)
		return (TR_NOT_HIT);
	i_v = dot_product(surf->cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
	if (i_v < 0 || i_v > 1)
		return (TR_NOT_HIT);
	*color = get_texture_color_at(i_v, i_u, surf->texture->colors);
	return (tr_correctify_color(color, i_r, sc));
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
		tr_result = tr_surface(ray, surf, pixel, sc);
		if (tr_result == TR_HIT)
			return ;
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
		t_ray ray, t_state *state)
{
	register int	x;
	register int	y;
	t_vec			*direction_p;
	int				pixel_index;

	direction_p = &(ray.direction);
	surfaces_sort(surfs);
	surfaces_pre_tr(*surfs, ray.origin);
	pixel_index = 0;
	y = 0;
	while (y < sc->screen_h)
	{
		x = 0;
		while (x < sc->screen_w)
		{
			vec_from_angles(direction_p, sc->x2yaw[x] + state->yaw,
					sc->y2pitch[y] + state->pitch);
			raytr_tr(sc, pixel_index, ray, *surfs);
			++pixel_index;
			++x;
		}
		++y;
	}
	draw_frame(sc);
}
