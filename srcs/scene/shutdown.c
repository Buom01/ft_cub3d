/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:35:23 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 16:59:19 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_shutdown(t_scene *scene)
{
	if (scene->map.data)
		free(scene->map.data);
	scene->map.data = NULL;
}
