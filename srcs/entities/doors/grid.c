/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:33:20 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 22:38:18 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_grid_update(t_door *door, t_ray ray,
		t_scene *scene, t_surface **lst_surf)
{
	t_surface	surf;
	t_surface	*surf_p;

	surf_p = init_door_surface(&surf, door->pos, 0.25);
	surf.texture = door->texture;
	if (door->vertical)
		surf.yaw = PI / 2;
	surf.pos.y += door->state * 0.85;
	surf.crop_y = -door->state * 0.85;
	submit_door_surface(surf_p, ray, scene, lst_surf);
}
