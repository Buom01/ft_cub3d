/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 06:26:23 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 17:33:38 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int		get_texture_color_at(double x, double y, const int *colors)
{
	return (colors[(int)((1 - x) * TEXTURE_SIZE)
		+ TEXTURE_SIZE * (int)((1 - y) * TEXTURE_SIZE)]);
}

inline int		*get_texture_color(int x, int y, int w, int *colors)
{
	return (colors + (y * w + x));
}
