/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:55:21 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 23:19:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screen_init(t_scene *sc)
{
	int		mock;
	size_t	display_w;
	size_t	display_h;

	if (!sc->save)
	{
		mlx_get_screen_size(sc->mlx, (int *)(&display_w), (int *)(&display_h));
		if (sc->screen_w > display_w)
			sc->screen_w = display_w;
		if (sc->screen_h > display_h)
			sc->screen_h = display_h;
		if (!sc->save && !(sc->window =
				mlx_new_window(sc->mlx, sc->screen_w, sc->screen_h, TITLE)))
			error(sc, ERR_MLX_UNKNOWN, NULL);
	}
	if (!(sc->frame = mlx_new_image(sc->mlx, sc->screen_w, sc->screen_h)))
		error(sc, ERR_MALLOC, NULL);
	sc->frame_colors = (int*)mlx_get_data_addr(sc->frame, &mock, &mock, &mock);
}

void	screen_shutdown(t_scene *scene)
{
	if (scene->frame)
		mlx_destroy_image(scene->mlx, scene->frame);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
}
