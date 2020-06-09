/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/06/09 01:39:13 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graphical_init(t_scene *sc)
{
	int	display_w;
	int	display_h;
	int mock;

	if (!(sc->mlx = mlx_init()))
		error(ERR_MLX_INIT, NULL);
	mlx_get_screen_size(sc->mlx, &display_w, &display_h);
	if (sc->screen_w > display_w)
		sc->screen_w = display_w;
	if (sc->screen_h > display_h)
		sc->screen_h = display_h;
	mlx_do_key_autorepeaton(sc->mlx);
	textures_load(sc);
	if (!(sc->window =
			mlx_new_window(sc->mlx, sc->screen_w, sc->screen_h, TITLE)))
		error(ERR_MLX_UNKNOWN, NULL);
	raytr_init(sc);
	if (!(sc->frame = mlx_new_image(sc->mlx, sc->screen_w, sc->screen_h)))
		error(ERR_MAP_MALLOC, NULL);
	sc->frame_colors = (int*)mlx_get_data_addr(sc->frame, &mock, &mock, &mock);
}

static int	graphical_update(t_scene *scene)
{
	t_state	*state;
	t_vec	player_vec;

	state = &(scene->state);
	player_vec.x = 1;
	player_vec.y = 0;
	player_vec.z = 0;
	ctrl_update(state);
	move_update(state);
	vec_rel_rot(&player_vec, AXIS_YAW, state->yaw);
	vec_rel_rot(&player_vec, AXIS_PITCH, state->pitch);
	raytr_render(scene, player_vec);
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

static void	graphical_shutdown(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->frame);
	mlx_destroy_window(scene->mlx, scene->window);
	raytr_shutdown(scene);
	textures_unload(scene);
	free(scene->mlx);
}

void		graphical_run(t_scene *scene)
{
	graphical_init(scene);
	graphical_main(scene);
	graphical_shutdown(scene);	
}
