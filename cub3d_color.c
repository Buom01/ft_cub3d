/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 23:06:36 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 00:10:43 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_x_color(t_color color)
{
	int x_color;

	x_color = color[0] << 16;
	x_color += color[1] << 8;
	x_color += color[2];
	return (x_color);
}