/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:26:56 by badam             #+#    #+#             */
/*   Updated: 2020/07/26 15:48:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_clicked(int btn, int x, int y, t_scene *scene)
{
	(void)btn;
	(void)x;
	(void)y;
	scene->focused = true;
	scene->mouse_in = true;
	scene_set_pause(scene, false);
	return (0);
}

int	window_focus_in(t_scene *scene)
{
	scene->focused = true;
	scene_set_pause(scene, !scene->mouse_in);
	return (0);
}

int	window_focus_out(t_scene *scene)
{
	scene->focused = false;
	scene_set_pause(scene, true);
	return (0);
}

int	window_mouse_in(t_scene *scene)
{
	scene->mouse_in = true;
	scene_set_pause(scene, !scene->focused);
	return (0);
}

int	window_mouse_out(t_scene *scene)
{
	scene->mouse_in = false;
	return (0);
}
