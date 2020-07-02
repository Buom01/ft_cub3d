/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surfaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:34:05 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 20:38:24 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_surface	*add_surface(t_surface **list, t_surface **last, t_scene *scene)
{
	t_surface	*surf;

	if (!(surf = malloc(sizeof(t_surface))))
		error(scene, ERR_MALLOC, NULL);
	ft_memset(surf, 0, sizeof(t_surface));
	if (!(*list))
		*list = surf;
	else
		(*last)->next = surf;
	*last = surf;
	return (surf);
}

void		free_surfaces(t_surface *surf)
{
	t_surface	*next;

	while (surf)
	{
		next = surf->next;
		free(surf);
		surf = next;
	}
}
