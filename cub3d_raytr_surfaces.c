/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_surfaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:32:40 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 23:16:58 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			add_surface(const t_surface *src, t_surface **rst,
		t_surface **lst, t_vec pos)
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

static inline bool	is_useful(t_surface *candidate, const t_scene *scene)
{
	return (true);
	// this is not OK, should take the location in account
	// should hide backface and offscreen
	return (fabs(fmod(candidate->yaw - scene->state.yaw + 90, 360)) < 180);
}

static void			surfaces_pre_tr(t_surface *surfs, t_vec rayorigin)
{
	t_vec	o_tr;

	while (surfs)
	{
		o_tr = vec_diff(rayorigin, surfs->o_t);
		surfs->cache.n_dot_o_tr = dot_product(surfs->base.n, o_tr);
		surfs->cache.o_tr_cross_v = cross_product(o_tr, surfs->base.v);
		surfs->cache.u_cross_o_tr = cross_product(surfs->base.u, o_tr);
		surfs = surfs->next;
	}
}

void				update_surface(t_surface *surf)
{
	surf->base.u.y = 1; 
	surf->base.v.x = COS(surf->yaw * TORAD);
	surf->base.v.z = SIN(surf->yaw * TORAD);
	surf->base.n = cross_product(surf->base.u, surf->base.v);
	surf->o_t.x = surf->pos.x - COS(surf->yaw * TORAD) * 0.5;
	surf->o_t.y = surf->pos.y - 0.5;
	surf->o_t.z = surf->pos.z - SIN(surf->yaw * TORAD) * 0.5;
}

void				raytr_get_surfaces(const t_scene *scene,
		t_surface **surfs, t_vec rayorigin)
{
	t_surface	*lstsurf;
	t_surface	*candidate;
	t_vec		pos;

	pos = scene->state.pos;
	lstsurf = NULL;
	*surfs = NULL;
	candidate = scene->surfaces;
	while (candidate)
	{
		if (is_useful(candidate, scene))
		{
			add_surface(candidate, surfs, &lstsurf, pos);
		}
		candidate = candidate->next;
	}
	if (lstsurf)
		lstsurf->next = NULL;
	surfaces_sort(surfs);
	surfaces_pre_tr(*surfs, rayorigin);
}
