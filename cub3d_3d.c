/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 22:08:58 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 04:35:11 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	vec_rel_rot(t_vec *vec, t_axis axis, t_angle alpha)
{
	t_vec	old;
	double	cos_alpha;
	double	sin_alpha;

	cos_alpha = cosf(alpha * TORAD);
	sin_alpha = sinf(alpha * TORAD);
	old = *vec;
	if (axis == AXIS_YAW)
	{
		vec->x = old.x * cos_alpha - old.z * sin_alpha;
		vec->z = old.x * sin_alpha + old.z * cos_alpha;
	}
	else if (axis == AXIS_PITCH)
	{
		vec->y = old.y * cos_alpha - old.z * sin_alpha;
		vec->z = old.y * sin_alpha + old.z * cos_alpha;
	}
	else if (axis == AXIS_ROLL)
	{
		vec->x = old.x * cos_alpha - old.y * sin_alpha;
		vec->y = old.x * sin_alpha + old.y * cos_alpha;
	}
}

inline double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

inline t_vec	vec_diff(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
