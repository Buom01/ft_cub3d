/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:03:26 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 00:56:33 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		items_shutdown(t_scene *scene)
{
	t_item	*item;
	t_item	*next;

	item = scene->items;
	while (item)
	{
		next = item->next;
		free(item);
		item = next;
	}
	scene->items = NULL;
}
