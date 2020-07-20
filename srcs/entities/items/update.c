/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 00:55:50 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 01:02:55 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	item_pickup(t_item *candidate, t_scene *sc)
{
	t_item	*prev;

	sc->state.inventory[candidate->type] = true;
	if (sc->items == candidate)
		sc->items = candidate->next;
	else
	{
		prev = sc->items;
		while (prev)
		{
			if (prev->next == candidate)
				prev->next = ((t_item *)prev->next)->next;
			prev = prev->next;
		}
	}
	free(candidate);
}

static bool	item_interact(t_item *candidate, t_scene *sc)
{
	if (dist_2d(sc->state.pos, candidate->pos) < 0.35)
	{
		item_pickup(candidate, sc);
		return (true);
	}
	return (false);
}

static bool	item_update(t_item *candidate, t_surface *surf,
		t_ray ray, t_scene *sc)
{
	if (!item_interact(candidate, sc))
	{
		candidate->animation += 0.035;
		ft_memset(surf, 0, sizeof(t_surface));
		surf->pos = candidate->pos;
		surf->pos.y += sin(candidate->animation) / 20 + 0.1;
		surf->texture = candidate->texture;
		surf->yaw = point_to(candidate->pos, ray.origin);
		return (true);
	}
	return (false);
}

void		items_update(t_scene *sc, t_state *state, t_ray ray,
		t_surface **lst_surf)
{
	t_item		*candidate;
	t_item		*next;
	t_surface	surf;
	t_surface	*surf_p;

	surf_p = &surf;
	candidate = sc->items;
	while (candidate)
	{
		next = candidate->next;
		if (item_update(candidate, surf_p, ray, sc)
				&& is_surface_useful(surf_p, ray, state->yaw, sc))
		{
			update_surface(surf_p);
			add_render_surface(surf_p, lst_surf, sc);
		}
		candidate = next;
	}
	if (*lst_surf)
		(*lst_surf)->next = NULL;
}
