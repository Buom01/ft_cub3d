/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:44:33 by badam             #+#    #+#             */
/*   Updated: 2020/07/11 04:24:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tr_correctify_color(int *color, double i_r, const t_scene *sc)
{
	if ((unsigned char)(*color >> 24) > 127)
		return (TR_NOT_HIT);
	if (sc->shadow)
		color_darken(color, (i_r - sc->shadow_begin) / sc->shadow_fade);
	return (TR_HIT);
}
