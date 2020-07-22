/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:46:34 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 23:06:35 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_frame(t_scene *sc)
{
	if (sc->save)
	{
		if (!write_image(sc->save, sc->frame_colors,
				sc->screen_w, sc->screen_h))
			error(sc, ERR_WRITEIMAGE, sc->save);
	}
	else
		mlx_put_image_to_window(sc->mlx, sc->window, sc->frame, 0, 0);
}

static int	tr_surface(t_ray ray, t_surface *surf, int *color,
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
	if (!(surf->backface) && n_dot_r > 0)
		return (TR_NOT_HIT);
	rev_n_dot_r = 1 / n_dot_r;
	i_r = -(surf->cache.n_dot_o_tr) * rev_n_dot_r;
	if (i_r < 0)
		return (TR_NOT_HIT);
	i_u = dot_product(surf->cache.o_tr_cross_v, ray.direction) * rev_n_dot_r;
	if (i_u < 0 || i_u > 1)
		return (TR_NOT_HIT);
	i_v = dot_product(surf->cache.u_cross_o_tr, ray.direction) * rev_n_dot_r;
	if (i_v < 0 || i_v > 1)
		return (TR_NOT_HIT);
	*color = get_texture_color_at(i_v, i_u, surf->texture, surf);
	return (tr_correctify_color(color, i_r, sc));
}

static void	raytr_tr(const t_scene *sc, int pixel_index,
		t_ray ray, t_surface *surfs)
{
	register int		tr_result;
	register t_surface	*surf;
	int					*pixel;

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
	if (ray.direction.y < -0.0001)
		tr_floor(ray, pixel, sc);
	else if (ray.direction.y > 0.0001)
		tr_ceil(ray, pixel, sc);
	else
		*pixel = 0;
}

void		raytr_render(t_scene *sc, t_surface **surfs,
		t_ray ray, t_state *state)
{
	register size_t	x;
	register size_t	y;
	register int	pixel_index;
	t_vec			vertical_direction;
	t_vec			rotaxis_cross_dir;

	surfaces_sort(surfs);
	surfaces_pre_tr(*surfs, ray.origin);
	ceilfloor_pre_tr(sc, ray.origin);
	pixel_index = 0;
	y = 0;
	while (y < sc->screen_h)
	{
		direction_rotaxis_from_state(&vertical_direction, &rotaxis_cross_dir,
			state->yaw, state->pitch + sc->y2pitch[y++]);
		x = 0;
		while (x < sc->screen_w)
		{
			optimized_rotate_vec(vertical_direction, sc->x2yaw[x++],
					rotaxis_cross_dir, &(ray.direction));
			raytr_tr(sc, pixel_index, ray, *surfs);
			++pixel_index;
		}
	}
	draw_frame(sc);
}
