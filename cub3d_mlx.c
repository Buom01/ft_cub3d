/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:36:49 by badam             #+#    #+#             */
/*   Updated: 2020/06/08 21:18:19 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_key	cub3d_mlx_tokey(t_syskey keycode)
{
	if (keycode == SYSKEY_ESC)
		return (KEY_ESC);
	else if (keycode == SYSKEY_LSHIFT)
		return (KEY_LSHIFT);
	else if (keycode == SYSKEY_LCTRL)
		return (KEY_LCTRL);
	else if (keycode == SYSKEY_F10)
		return (KEY_F10);
	else if (keycode == SYSKEY_F11)
		return (KEY_F11);
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
