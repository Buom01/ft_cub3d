/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:48:54 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graphical_init(t_scene *sc)
{
	int	display_w;
	int	display_h;
	int mock;

	if (!(sc->mlx = mlx_init()))
		error(sc, ERR_MLX_INIT, NULL);
	mlx_get_screen_size(sc->mlx, &display_w, &display_h);
	if (sc->screen_w > display_w)
		sc->screen_w = display_w;
	if (sc->screen_h > display_h)
		sc->screen_h = display_h;
	textures_load(sc);
	if (!(sc->window =
			mlx_new_window(sc->mlx, sc->screen_w, sc->screen_h, TITLE)))
		error(sc, ERR_MLX_UNKNOWN, NULL);
	physics_init(&(sc->map), sc);
	walls_init(sc);
	raytr_init(sc);
	if (!(sc->frame = mlx_new_image(sc->mlx, sc->screen_w, sc->screen_h)))
		error(sc, ERR_MALLOC, NULL);
	sc->frame_colors = (int*)mlx_get_data_addr(sc->frame, &mock, &mock, &mock);
}

static int	graphical_update(t_scene *sc)
{
	t_state	*state;

	state = &(sc->state);
	ctrl_update(sc, state);
	move_update(state);
	raytr_render(sc, state, sc->screen_w, sc->screen_h);
	return (0);
}

static void	graphical_main(t_scene *sc)
{
	t_state	*state;

	state = &(sc->state);
	mlx_hook(sc->window, KEYPRESS, KEYPRESSMASK, ctrl_keypress, state);
	mlx_hook(sc->window, KEYRELEASE, KEYRELEASEMASK, ctrl_keyrelease, state);
	mlx_loop_hook(sc->mlx, graphical_update, sc);
	mlx_loop(sc->mlx);
}

void		graphical_shutdown(t_scene *scene)
{
	if (scene->frame)
		mlx_destroy_image(scene->mlx, scene->frame);
	if (scene->window)
		mlx_destroy_window(scene->mlx, scene->window);
	if (scene->mlx)
	{
		textures_unload(scene);
		free(scene->mlx);
	}
	physics_shutdown(&(scene->map));
	walls_shutdown(scene);
	scene_shutdown(scene);
}

void		graphical_run(t_scene *scene)
{
	graphical_init(scene);
	graphical_main(scene);
	graphical_shutdown(scene);	
}
