/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:37:34 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:12:33 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ctrl_keypress(t_syskey keycode, t_state *state)
{
	t_key	key;

	key = cub3d_mlx_tokey(keycode);
	if (key != KEY_UNKNOWN)
		state->keyboard[key] = true;
	return (0);
}

int		ctrl_keyrelease(t_syskey keycode, t_state *state)
{
	t_key	key;

	key = cub3d_mlx_tokey(keycode);
	if (key != KEY_UNKNOWN)
		state->keyboard[key] = false;
	return (0);
}

void	ctrl_releaseall(t_state *state)
{
	ft_memset(&(state->keyboard), sizeof(state->keyboard), 0);
	state->mouse_x = 0;
	state->mouse_y = 0;
}

void	ctrl_update(t_scene *scene, t_state *state)
{
	if (state->keyboard[KEY_ESC])
	{
		graphical_shutdown(scene);
		exit(EXIT_SUCCESS);
	}
	state->crouch = state->keyboard[KEY_LSHIFT];
	if (state->keyboard[KEY_LCTRL])
	{
		if (state->keyboard[KEY_UP])
			state->pitch -= 3;
		if (state->keyboard[KEY_DOWN])
			state->pitch += 3;
		if (state->keyboard[KEY_LEFT])
			move_side(state, 1);
		if (state->keyboard[KEY_RIGHT])
			move_side(state, -1);
	}
	else
	{
		if (state->keyboard[KEY_UP])
			move_forward(state, 1);
		if (state->keyboard[KEY_DOWN])
			move_forward(state, -1);
		if (state->keyboard[KEY_LEFT])
			state->yaw -= 5;
		if (state->keyboard[KEY_RIGHT])
			state->yaw += 5;
	}
	if (state->keyboard[KEY_SPACE])
		jump(state);
	state->yaw += state->mouse_x;
	state->pitch += state->mouse_y;
	state->mouse_x = 0;
	state->mouse_y = 0;
}
