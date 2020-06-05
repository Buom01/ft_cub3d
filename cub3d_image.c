/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 06:26:23 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 06:42:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int		get_texture_color(double x, double y, int *colors)
{
	return (colors[(int)round(x * (TEXTURE_SIZE - 1))
		+ TEXTURE_SIZE * (int)((1.0 - y) * (TEXTURE_SIZE - 1))]);
}

inline void		set_texture_color(int *colors, int w, int x, int y, int color)
{
	colors[y * w + x] = color;
}
