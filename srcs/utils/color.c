/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 23:06:36 by badam             #+#    #+#             */
/*   Updated: 2020/07/11 04:13:34 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			to_x_color(t_color *color)
{
	int x_color;

	x_color = color->alpha << 24;
	x_color = color->red << 16;
	x_color += color->green << 8;
	x_color += color->blue;
	return (x_color);
}

void		color_darken(int *color, double dark_ratio)
{
	t_color	darked;
	double	factor;

	if (dark_ratio < 0)
		return ;
	if (dark_ratio > 1)
	{
		*color = 0;
		return ;
	}
	factor = 1 - dark_ratio;
	darked.alpha = (unsigned char)(*color >> 24);
	darked.red = (unsigned char)(*color >> 16) * factor;
	darked.green = (unsigned char)(*color >> 8) * factor;
	darked.blue = (unsigned char)(*color) * factor;
	*color = to_x_color(&darked);
}

inline int	fade_color(int c1, int c2, double balance)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (unsigned char)(c1 >> 24) * (1 - balance)
			+ (unsigned char)(c2 >> 24) * balance;
	r = (unsigned char)(c1 >> 16) * (1 - balance)
			+ (unsigned char)(c2 >> 16) * balance;
	g = (unsigned char)(c1 >> 8) * (1 - balance)
			+ (unsigned char)(c2 >> 8) * balance;
	b = (unsigned char)(c1) * (1 - balance)
			+ (unsigned char)(c2) * balance;
	return ((a << 24) + (r << 16) + (g << 8) + b);
}
