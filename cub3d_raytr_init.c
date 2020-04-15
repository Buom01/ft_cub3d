/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:07:12 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 02:43:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_surround_surfaces(t_scene *scene, size_t pos, t_surface **lastsurf)
{
	(void)lastsurf;
	if (!scene->map.walkable[pos])
		return;
//	if (!scene->
}

void	raytracing_init(t_scene *scene)
{
	size_t 		pos;
	t_surface	*lastsurf;

	pos = 0;
	while (pos < scene->map.length)
		add_surround_surfaces(scene, pos++, &lastsurf);
}
