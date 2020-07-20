/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:33:20 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 23:45:39 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_grid_update(t_door *door, t_ray ray,
		t_scene *scene, t_surface **lst_surf)
{
	t_surface	surf;
	t_surface	*surf_p;

	surf_p = init_door_surface(&surf, door->pos);
	surf.texture = door->texture;
	if (door->vertical)
		surf.yaw = 90;
	surf.pos.y += door->state;
	surf.crop_y = -door->state;
	submit_door_surface(surf_p, ray, scene, lst_surf);
}
