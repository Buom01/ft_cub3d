/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 23:29:18 by badam             #+#    #+#             */
/*   Updated: 2020/07/21 14:25:25 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_surface	*init_door_surface(t_surface *surf, t_pos pos, double special)
{
	ft_memset(surf, 0, sizeof(t_surface));
	surf->pos = pos;
	surf->backface = true;
	surf->special = special;
	return (surf);
}

void		submit_door_surface(t_surface *surf, t_ray ray, t_scene *sc,
		t_surface **lst_surf)
{
	if (is_surface_useful(surf, ray, sc->state.yaw, sc))
	{
		update_surface(surf);
		add_render_surface(surf, lst_surf, sc);
	}
}
