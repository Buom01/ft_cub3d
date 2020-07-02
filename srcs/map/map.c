/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 05:06:05 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 20:19:39 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_map(t_scene *scene)
{
	if (!scene->map.data)
		return (false);
	scene->map.length = scene->map.width * scene->map.height;
	init_player(&scene->map, scene);
	return (true);
}
