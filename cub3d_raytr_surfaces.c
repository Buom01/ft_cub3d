/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_surfaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:32:40 by badam             #+#    #+#             */
/*   Updated: 2020/04/30 16:17:50 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_surface(t_surface *src, t_surface **rst, t_surface **lst,
		t_vec pos)
{
	t_surface	*surf;

	if (!(surf = malloc(sizeof(t_surface))))
		error(ERR_MAP_MALLOC, NULL);
	ft_memcpy(surf, src, sizeof(t_surface));
	surf->distance = dist_2d(&(surf->pos), &pos); 
	if (!(*rst))
		*rst = surf;
	else
		(*lst)->next = surf;
	*lst = surf;
}

static bool	is_useful(t_surface *candidate, t_scene *scene)
{
	// this is not OK, should take the location in account
	// should hide backface and offscreen

	return (fabs(fmod(candidate->yaw - scene->state.yaw, 360)) < 180);
}

void		raytr_get_surfaces(t_scene *scene, t_surface **surfs)
{
	t_surface	*lstsurf;
	t_surface	*candidate;
	t_vec		pos;

	pos = scene->state.pos;
	(void)pos;
	(void)add_surface;
	(void)surfs;
	lstsurf = NULL;
	candidate = scene->surfaces;
	while (candidate)
	{
		if (is_useful(candidate, scene))
		{
			//add_surface(candidate, surfs, &lstsurf, pos);
		}
		candidate = candidate->next;
	}
	if (lstsurf)
		lstsurf->next = NULL;
	//surfaces_sort(surfs);
}
