/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 06:26:23 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 14:32:07 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int		get_texture_color_at(double x, double y, const int *colors)
{
	return (colors[(int)round(x * (TEXTURE_SIZE - 1))
		+ TEXTURE_SIZE * (int)((1.0 - y) * (TEXTURE_SIZE - 1))]);
}

inline int		*get_texture_color(int x, int y, int w, int *colors)
{
	return (colors + (y * w + x));
}

inline void		set_texture_color(int x, int y, int w, int *colors, int color)
{
	colors[y * w + x] = color;
}
