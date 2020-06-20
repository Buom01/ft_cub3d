/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:51:50 by badam             #+#    #+#             */
/*   Updated: 2020/06/20 16:47:34 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline double	dist_2d(t_vec a, t_vec b)
{
	double x;
	double z;

	x = a.x - b.x;
	x *= x;
	z = a.z - b.z;
	z *= z;
	return (sqrt(x + z));
}

inline t_angle	point_to(t_pos from, t_pos to)
{
	double	x;
	double	z;

	x = to.x - from.x;
	z = to.z - from.z;
	if (z < 0)
		return (-atan(x / z) * TODEG);
	else
		return (-atan(x / z) * TODEG + 180);
}
