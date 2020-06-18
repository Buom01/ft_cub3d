/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:35:23 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:53:46 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_shutdown(t_scene *scene)
{
	if (scene->north.path)
		free(scene->north.path);
	if (scene->south.path)
		free(scene->south.path);
	if (scene->west.path)
		free(scene->west.path);
	if (scene->east.path)
		free(scene->east.path);
	if (scene->sprite.path)
		free(scene->sprite.path);
	if (scene->map.data)
		free(scene->map.data);
}
