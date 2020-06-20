/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:51:25 by badam             #+#    #+#             */
/*   Updated: 2020/06/20 18:47:04 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MLX_H
# define CUB3D_MLX_H

# define KEYPRESS 2
# define KEYRELEASE 3
# define MOUSEPRESS 4
# define MOUSERELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8

# define NOEVENTMASK 0L
# define KEYPRESSMASK 1L
# define KEYRELEASEMASK 2L
# define MOUSEPRESSMASK 4L
# define MOUSERELEASEMASK 8L
# define ENTERWINDOWMASK 16L
# define LEAVEWINDOWMASK 32L
# define POINTERMOTIONMASK 64L
# define POINTERMOTIONHINTMASK 128L

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

typedef enum
{
# ifdef __APPLE__
	SYSKEY_ESC = 53,
	SYSKEY_TAB = 48,
	SYSKEY_LSHIFT = 257,
	SYSKEY_LCTRL = 256,
	SYSKEY_RSHIFT = 258,
	SYSKEY_RCTRL = 269,
	SYSKEY_ENTER = 36,
	SYSKEY_F1 = 122,
	SYSKEY_F2 = 120,
	SYSKEY_F3 = 99,
	SYSKEY_F4 = 118,
	SYSKEY_F5 = 96,
	SYSKEY_F6 = 97,
	SYSKEY_F7 = 98,
	SYSKEY_F8 = 100,
	SYSKEY_F9 = 101,
	SYSKEY_F10 = 109,
	SYSKEY_F11 = 103,
	SYSKEY_F12 = 111,
	SYSKEY_W = 13,
	SYSKEY_A = 0,
	SYSKEY_S = 1,
	SYSKEY_D = 2,
	SYSKEY_SPACE = 49,
	SYSKEY_UP = 126,
	SYSKEY_RIGHT = 124,
	SYSKEY_DOWN = 125,
	SYSKEY_LEFT = 123
#else
	SYSKEY_ESC = 65307,
	SYSKEY_TAB = 65289,
	SYSKEY_LSHIFT = 65505,
	SYSKEY_LCTRL = 65507,
	SYSKEY_RSHIFT = 65506,
	SYSKEY_RCTRL = 65312,
	SYSKEY_ENTER = 65293,
	SYSKEY_F1 = 65470,
	SYSKEY_F2 = 65471,
	SYSKEY_F3 = 65472,
	SYSKEY_F4 = 65473,
	SYSKEY_F5 = 65474,
	SYSKEY_F6 = 65475,
	SYSKEY_F7 = 65476,
	SYSKEY_F8 = 65477,
	SYSKEY_F9 = 65478,
	SYSKEY_F10 = 65479,
	SYSKEY_F11 = 65480,
	SYSKEY_F12 = 65481,
	SYSKEY_W = 119,
	SYSKEY_A = 97,
	SYSKEY_S = 115,
	SYSKEY_D = 100,
	SYSKEY_SPACE = 32,
	SYSKEY_UP = 65362,
	SYSKEY_RIGHT = 65363,
	SYSKEY_DOWN = 65364,
	SYSKEY_LEFT = 65361
# endif
}	t_syskey;

#endif
