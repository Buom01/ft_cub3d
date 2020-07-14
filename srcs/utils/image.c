/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 06:26:23 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 13:32:31 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int		get_texture_color_at(double x, double y, const t_texture *tex)
{
	return (tex->colors[(int)((1 - x) * tex->width)
		+ tex->width * (int)((1 - y) * tex->height)]);
}
