/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 22:38:42 by badam             #+#    #+#             */
/*   Updated: 2020/07/19 22:11:44 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		sign(double n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}

float	born(float val, float min, float max)
{
	if (val < min)
		val = min;
	else if (val > max)
		val = max;
	return (val);
}
