/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surfaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:32:40 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:33:42 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static void	add_render_surface(const t_surface *src, t_surface **rst,
		t_surface **lst, t_scene *scene)
{
	t_surface	*surf;

	if (!(surf = malloc(sizeof(t_surface))))
		error(scene, ERR_MALLOC, NULL);
	ft_memcpy(surf, src, sizeof(t_surface));
	if (!(*rst))
		*rst = surf;
	else
		(*lst)->next = surf;
	*lst = surf;
}

static inline bool	is_useful(t_surface *candidate, t_ray ray, t_angle yaw)
{
	t_vec	diff;
	t_pos	filter_origin;

	filter_origin.y = ray.origin.y;
	filter_origin.x = ray.origin.x - SIN(yaw * TORAD) / 2;
	filter_origin.z = ray.origin.z - COS(yaw * TORAD) / 2;
	candidate->cache.distance = dist_2d(candidate->pos, ray.origin);
	if (MAX_DIST)
		if (candidate->cache.distance > MAX_DIST + 0.5)
			return (false);
	diff = vec_diff(candidate->pos, filter_origin);
	if (dot_product(diff, ray.direction) < 0)
		return (false);
	return (true);
}

static void			surfaces_pre_tr(t_surface *surfs, t_pos origin)
{
	t_vec	o_tr;

	while (surfs)
	{
		o_tr = vec_diff(origin, surfs->o_t);
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

void				raytr_get_surfaces(t_surface **surfs, t_ray ray,
		t_surface *scsurfs, t_scene *scene)
{
	t_surface	*lstsurf;
	t_surface	*candidate;
	t_state		*state;

	state = &(scene->state);
	lstsurf = NULL;
	*surfs = NULL;
	candidate = scsurfs;
	while (candidate)
	{
		if (is_useful(candidate, ray, state->yaw))
			add_render_surface(candidate, surfs, &lstsurf, scene);
		candidate = candidate->next;
	}
	if (lstsurf)
		lstsurf->next = NULL;
	surfaces_sort(surfs);
	surfaces_pre_tr(*surfs, ray.origin);
}