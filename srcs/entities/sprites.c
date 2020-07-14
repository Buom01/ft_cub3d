/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:03:26 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 14:04:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprites_init(t_scene *scene)
{
	size_t		i;
	t_map		*map;
	t_sprite	*sprite;
	t_sprite	*lst;

	map = &(scene->map);
	lst = NULL;
	i = 0;
	while (i < map->length)
	{
		if (map->data[i] == MAP_OBJECT)
		{
			if (!(sprite = malloc(sizeof(t_sprite))))
				error(scene, ERR_MALLOC, NULL);
			ft_memset(sprite, 0, sizeof(t_sprite));
			sprite->texture = &(scene->sprite);
			sprite->pos = i2pos(map, i, DIR_NONE);
			if (!(scene->sprites))
				scene->sprites = sprite;
			if (lst)
				lst->next = sprite;
			lst = sprite;
		}
		++i;
	}
}

void		sprites_update(t_scene *sc, t_state *state, t_ray ray,
		t_surface **lst_surf)
{
	t_sprite	*candidate;
	t_surface	surf;
	t_surface	*surf_p;

	surf_p = &surf;
	candidate = sc->sprites;
	while (candidate)
	{
		ft_memset(surf_p, 0, sizeof(t_surface));
		surf.pos = candidate->pos;
		surf.texture = candidate->texture;
		surf.yaw = point_to(candidate->pos, ray.origin);
		if (is_surface_useful(surf_p, ray, state->yaw, sc))
		{
			update_surface(surf_p);
			add_render_surface(surf_p, lst_surf, sc);
		}
		candidate = candidate->next;
	}
	if (*lst_surf)
		(*lst_surf)->next = NULL;
}

void		sprites_shutdown(t_scene *scene)
{
	t_sprite	*sprite;
	t_sprite	*next;

	sprite = scene->sprites;
	while (sprite)
	{
		next = sprite->next;
		free(sprite);
		sprite = next;
	}
	scene->sprites = NULL;
}
