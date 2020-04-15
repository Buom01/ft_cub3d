/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/04/14 01:41:56 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graphical_init(t_scene *scene, void **mlx, void **window)
{
	if (!(*mlx = mlx_init()))
		error(ERR_MLX_INIT, NULL);
	textures_load(scene, *mlx);
	if (!(*window =
			mlx_new_window(*mlx, scene->screen_w, scene->screen_h, "Cub3D")))
		error(ERR_MLX_UNKNOWN, NULL);
	raytracing_init(scene);
}

static void	graphical_main(t_scene *scene, void *mlx, void *window)
{
	while (1)
	{
		mlx_clear_window(mlx, window);
		//controls_update(scene, mlx, window);
		//raytracing_render(mlx, window, t_scene scene);
		(void)scene;
	}
}

static void	graphical_shutdown(t_scene *scene, void *mlx, void *window)
{
	mlx_destroy_window(mlx, window);
	textures_unload(scene, mlx);
	free(mlx);
}

void		graphical_run(t_scene *scene)
{
	void	*mlx;
	void	*window;

	graphical_init(scene, &mlx, &window);
	graphical_main(scene, mlx, window);
	graphical_shutdown(scene, mlx, window);	
}
