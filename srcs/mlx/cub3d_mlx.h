/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:51:25 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 22:54:51 by badam            ###   ########.fr       */
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

#endif
