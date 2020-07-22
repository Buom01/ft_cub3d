/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 22:08:58 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 16:22:31 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_from_state(t_vec *dir, t_angle yaw, t_angle pitch)
{
	double	cos_pitch;

	cos_pitch = COS(pitch * TORAD);
	dir->x = SIN(yaw * TORAD) * cos_pitch;
	dir->z = -COS(yaw * TORAD) * cos_pitch;
	dir->y = -SIN(pitch * TORAD);
}

void	direction_rotaxis_from_state(t_vec *dir, t_vec *rotaxis_cross_dir,
		t_angle yaw, t_angle pitch)
{
	double	cos_pitch;
	double	cos_yaw;
	double	sin_yaw;

	cos_pitch = COS(pitch * TORAD);
	cos_yaw = COS(yaw * TORAD);
	sin_yaw = SIN(yaw * TORAD);
	dir->x = sin_yaw * cos_pitch;
	dir->z = -cos_yaw * cos_pitch;
	dir->y = -SIN(pitch * TORAD);
	rotaxis_cross_dir->x = cos_yaw;
	rotaxis_cross_dir->z = sin_yaw;
	rotaxis_cross_dir->y = 0;
}

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec	vec_diff(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
