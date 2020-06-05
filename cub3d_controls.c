/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 22:37:34 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 02:26:10 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	controls_update(t_scene *scene, t_vec *player_vec)
{
	player_vec->x = 1;
	player_vec->y = 0;
	player_vec->z = 0;

	scene->state.yaw += 10;
	vec_rel_rot(player_vec, AXIS_YAW, scene->state.yaw);
}
