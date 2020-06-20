/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 19:11:35 by badam             #+#    #+#             */
/*   Updated: 2020/06/20 20:16:45 by badam            ###   ########.fr       */
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

int		ctrl_mousemove(int x, int y, t_scene *sc)
{
	sc->state.mouse_x += x - sc->mouse_origin_x;
	sc->state.mouse_y += y - sc->mouse_origin_y;
	mlx_mouse_move(sc->mlx, sc->window, sc->mouse_origin_x, sc->mouse_origin_y);
	return (0);
}
