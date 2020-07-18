/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:33:20 by badam             #+#    #+#             */
/*   Updated: 2020/07/18 14:14:38 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_surface	*init_surface(t_surface *surf, t_pos pos)
{
	ft_memset(surf, 0, sizeof(t_surface));
	surf->pos = pos;
	surf->backface = true;
	return (surf);
}

static void			submit_surface(t_surface *surf, t_ray ray, t_scene *sc,
		t_surface **lst_surf)
{
	if (is_surface_useful(surf, ray, sc->state.yaw, sc))
	{
		update_surface(surf);
		add_render_surface(surf, lst_surf, sc);
	}
}

void				door_standard_update(t_door *door, t_ray ray,
		t_scene *scene, t_surface **lst_surf)
{
	t_surface	surf_a;
	t_surface	surf_b;
	t_surface	*surf_a_p;
	t_surface	*surf_b_p;

	surf_a_p = init_surface(&surf_a, door->pos);
	surf_b_p = init_surface(&surf_b, door->pos);
	surf_a.texture = door->texture;
	surf_b.texture = door->texture + sizeof(t_surface);
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
	submit_surface(surf_a_p, ray, scene, lst_surf);
	submit_surface(surf_b_p, ray, scene, lst_surf);
}
