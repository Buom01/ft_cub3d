/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:33:20 by badam             #+#    #+#             */
/*   Updated: 2020/07/21 14:28:39 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_standard_update(t_door *door, t_ray ray,
		t_scene *scene, t_surface **lst_surf)
{
	t_surface	surf_a;
	t_surface	surf_b;
	t_surface	*surf_a_p;
	t_surface	*surf_b_p;

	surf_a_p = init_door_surface(&surf_a, door->pos, door->state / 8);
	surf_b_p = init_door_surface(&surf_b, door->pos, door->state / 8);
	surf_a.texture = door->texture;
	surf_b.texture = door->texture_b;
	if (door->vertical)
	{
		surf_a.yaw = 90;
		surf_b.yaw = 90;
		surf_a.pos.z += door->state / 2;
		surf_b.pos.z -= door->state / 2;
	}
	else
	{
		surf_a.pos.x += door->state / 2;
		surf_b.pos.x -= door->state / 2;
	}
	surf_a.crop_x = -door->state / 2;
	surf_b.crop_x = +door->state / 2;
	submit_door_surface(surf_a_p, ray, scene, lst_surf);
	submit_door_surface(surf_b_p, ray, scene, lst_surf);
}
