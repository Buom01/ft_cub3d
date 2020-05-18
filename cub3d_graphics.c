/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/05/08 21:30:27 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graphical_init(t_scene *sc)
{
	if (!(sc->mlx = mlx_init()))
		error(ERR_MLX_INIT, NULL);
	textures_load(sc);
	if (!(sc->window =
			mlx_new_window(sc->mlx, sc->screen_w, sc->screen_h, "Cub3D")))
		error(ERR_MLX_UNKNOWN, NULL);
	raytr_init(sc);
}

static void	graphical_main(t_scene *scene)
{
	t_vec	p_vec;

	while (1)
	{
		mlx_clear_window(scene->mlx, scene->window);
		//controls_update(scene);
		p_vec.x = 1 * sin(scene->state.yaw * TORAD);
		p_vec.y = 1 * cos(scene->state.yaw * TORAD);
		p_vec.z = 0;
		raytr_render(scene, p_vec);
	}
}

static void	graphical_shutdown(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->window);
	raytr_shutdown(scene);
	textures_unload(scene);
	free(scene->mlx);
}

void		graphical_run(t_scene *scene)
{
	graphical_init(scene);
	graphical_main(scene);
	graphical_shutdown(scene);	
}
