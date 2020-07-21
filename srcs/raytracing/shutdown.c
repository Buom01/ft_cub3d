/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:10:07 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 17:07:30 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raytr_shutdown(t_scene *sc)
{
	if (sc->x2yaw)
		free(sc->x2yaw);
	if (sc->y2pitch)
		free(sc->y2pitch);
	sc->x2yaw = NULL;
	sc->y2pitch = NULL;
}
