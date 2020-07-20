/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 00:22:22 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 00:22:54 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_item(t_entity ent)
{
	return (ent == MAP_KEY);
}

static void	init_item_from_type(t_item *item, t_entity ent, t_scene *sc)
{
	if (ent == MAP_KEY)
	{
		item->type = ITEM_KEY;
		item->texture = &(sc->key);
	}
}

void		items_init(t_scene *scene, t_map *map)
{
	size_t	i;
	t_item	*item;
	t_item	*lst;

	lst = NULL;
	i = 0;
	while (i < map->length)
	{
		if (is_item(map->data[i]))
		{
			if (!(item = malloc(sizeof(t_item))))
				error(scene, ERR_MALLOC, NULL);
			ft_memset(item, 0, sizeof(t_item));
			item->pos = i2pos(map, i, DIR_NONE);
			init_item_from_type(item, map->data[i], scene);
			if (!(scene->items))
				scene->items = item;
			if (lst)
				lst->next = item;
			lst = item;
		}
		++i;
	}
}
