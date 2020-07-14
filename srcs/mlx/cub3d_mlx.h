/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:51:25 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 13:32:53 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MLX_H
# define CUB3D_MLX_H

# ifdef __APPLE__
#  include "cub3d_mlx_apple.h"
# else
#  include "cub3d_mlx_linux.h"
# endif

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8
# define FOCUSIN 9
# define FOCUSOUT 10
# define KEYMAPNOTIFY 11
# define EXPOSE 12
# define GRAPHICSEXPOSE 13
# define NOEXPOSE 14
# define VISIBILITYNOTIFY 15
# define CREATENOTIFY 16
# define DESTROYNOTIFY 17
# define UNMAPNOTIFY 18
# define MAPNOTIFY 19
# define MAPREQUEST 20
# define REPARENTNOTIFY 21
# define CONFIGURENOTIFY 22
# define CONFIGUREREQUEST 23
# define GRAVITYNOTIFY 24

# define NOEVENTMASK 0
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 2
# define BUTTONPRESSMASK 4
# define BUTTONRELEASEMASK 8
# define ENTERWINDOWMASK 16
# define LEAVEWINDOWMASK 32
# define POINTERMOTIONMASK 64
# define POINTERMOTIONHINTMASK 128
# define BUTTON1MOTIONMASK 256
# define BUTTON2MOTIONMASK 512
# define BUTTON3MOTIONMASK 1024
# define BUTTON4MOTIONMASK 2048
# define BUTTON5MOTIONMASK 4096
# define BUTTONMOTIONMASK 8192
# define KEYMAPSTATEMASK 16384
# define EXPOSUREMASK 32768
# define VISIBILITYCHANGEMASK 65536
# define STRUCTURENOTIFYMASK 131072
# define RESIZEREDIRECTMASK 262144
# define SUBSTRUCTURENOTIFYMASK 524288
# define SUBSTRUCTUREREDIRECTMASK 1048576
# define FOCUSCHANGEMASK 2097152
# define PROPERTYCHANGEMASK 4194304
# define COLORMAPCHANGEMASK 8388608
# define OWNERGRABBUTTONMASK 16777216

typedef enum
{
	MOUSE1 = 1,
	MOUSE2,
	MOUSE3,
	SCROLLUP,
	SCROLLDOWN,
	SCROLLLEFT,
	SCROLLRIGHT
}	t_mouse;

#endif
