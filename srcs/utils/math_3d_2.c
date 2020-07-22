/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_3d_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:23:52 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 22:34:14 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	Rodrigues' rotation formula;
**	Axis and vector are always perpendicular which permit some simplifications.
**	For the same reason the cross product could be calculated directly.
*/

void	optimized_rotate_vec(t_vec vec, t_angle phy,
		t_vec axis_cross_vec, t_vec *out)
{
	double	cos_phy;
	double	sin_phy;

	cos_phy = COS(phy);
	sin_phy = SIN(phy);
	out->x = vec.x * cos_phy + axis_cross_vec.x * sin_phy;
	out->y = vec.y * cos_phy + axis_cross_vec.y * sin_phy;
	out->z = vec.z * cos_phy + axis_cross_vec.z * sin_phy;
}
