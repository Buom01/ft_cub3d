/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raytr_shutdown.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 19:06:07 by badam             #+#    #+#             */
/*   Updated: 2020/04/29 21:48:15 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raytr_free_surfs(t_surface *surf)
{
	t_surface	*next;

	while(surf)
	{
		next = surf->next;
		free(surf);
		surf = next;
	}
}

void	raytr_shutdown(t_scene *scene)
{
	raytr_free_surfs(scene->surfaces);
	scene->surfaces = NULL;
}
