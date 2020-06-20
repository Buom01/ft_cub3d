/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:36:49 by badam             #+#    #+#             */
/*   Updated: 2020/06/20 18:36:23 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_key	cub3d_mlx_tokey(t_syskey keycode)
{
	if (keycode == SYSKEY_ESC)
		return (KEY_ESC);
	else if (keycode == SYSKEY_LSHIFT)
		return (KEY_LSHIFT);
	else if (keycode == SYSKEY_W)
		return (KEY_W);
	else if (keycode == SYSKEY_A)
		return (KEY_A);
	else if (keycode == SYSKEY_S)
		return (KEY_S);
	else if (keycode == SYSKEY_D)
		return (KEY_D);
	else if (keycode == SYSKEY_SPACE)
		return (KEY_SPACE);
	else if (keycode == SYSKEY_UP)
		return (KEY_UP);
	else if (keycode == SYSKEY_RIGHT)
		return (KEY_RIGHT);
	else if (keycode == SYSKEY_DOWN)
		return (KEY_DOWN);
	else if (keycode == SYSKEY_LEFT)
		return (KEY_LEFT);
	else
		return (KEY_UNKNOWN);
}
