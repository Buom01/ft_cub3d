/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:37:34 by badam             #+#    #+#             */
/*   Updated: 2020/07/13 00:00:45 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ctrl_init(t_scene *sc)
{
	t_state	*state;

	if (sc->save)
		return;
	state = &(sc->state);
	sc->mouse_origin_x = sc->screen_w / 2;
	sc->mouse_origin_y = sc->screen_h / 2;
	mlx_mouse_hide(sc->mlx, sc->window);
	mlx_hook(sc->window, KEYPRESS, KEYPRESSMASK, ctrl_keypress, state);
	mlx_hook(sc->window, KEYRELEASE, KEYRELEASEMASK, ctrl_keyrelease, state);
	mlx_hook(sc->window, MOTIONNOTIFY, POINTERMOTIONMASK, ctrl_mousemove, sc);
}

void		ctrl_update(t_scene *scene, t_state *state)
{
	if (state->keyboard[KEY_ESC])
		main_stopall(scene);
	state->crouch = state->keyboard[KEY_LSHIFT];
	if (state->keyboard[KEY_W])
		move_forward(state, 1);
	if (state->keyboard[KEY_A])
		move_side(state, 1);
	if (state->keyboard[KEY_S])
		move_forward(state, -1);
	if (state->keyboard[KEY_D])
		move_side(state, -1);
	if (state->keyboard[KEY_LEFT])
		state->yaw -= 5;
	if (state->keyboard[KEY_RIGHT])
		state->yaw += 5;
	if (state->keyboard[KEY_SPACE])
		jump(state);
	state->yaw += state->mouse_x * 0.04;
	state->pitch += state->mouse_y * 0.04;
	if (state->pitch > 90)
		state->pitch = 90;
	if (state->pitch < -90)
		state->pitch = -90;
	state->mouse_x = 0;
	state->mouse_y = 0;
}

void		ctrl_shutdown(t_scene *scene)
{
	if (scene->mlx && scene->window)
		mlx_mouse_show(scene->mlx, scene->window);
}
