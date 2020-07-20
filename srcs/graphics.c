/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 00:07:31 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graphical_init(t_scene *sc)
{
	t_map	*map;

	map = &(sc->map);
	if (!(sc->mlx = mlx_init()))
		error(sc, ERR_MLX_INIT, NULL);
	screen_init(sc);
	textures_load(sc);
	ctrl_init(sc);
	physics_init(map, sc);
	walls_init(sc, map);
	fakewalls_init(sc, map);
	sprites_init(sc, map);
	items_init(sc, map);
	doors_init(sc, map);
	raytr_init(sc);
}

static int	graphical_update(t_scene *sc)
{
	t_state		*state;
	t_ray		ray;
	t_surface	*rendr_surfs;
	t_surface	*lst_rendr_surf;

	state = &(sc->state);
	ray.origin = state->pos;
	vec_from_angles(&(ray.direction), state->yaw, state->pitch);
	rendr_surfs = NULL;
	lst_rendr_surf = NULL;
	ctrl_update(sc, state);
	move_update(state);
	physics_apply(sc);
	walls_update(sc, ray, &lst_rendr_surf, &rendr_surfs);
	sprites_update(sc, state, ray, &lst_rendr_surf);
	items_update(sc, state, ray, &lst_rendr_surf);
	doors_update(sc, ray, &lst_rendr_surf);
	raytr_render(sc, &rendr_surfs, ray, state);
	free_surfaces(rendr_surfs);
	mlx_do_sync(sc->mlx);
	return (0);
}

static void	graphical_main(t_scene *sc)
{
	if (sc->save)
	{
		graphical_update(sc);
	}
	else
	{
		mlx_hook(sc->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
			main_stopall, sc);
		mlx_loop_hook(sc->mlx, graphical_update, sc);
		mlx_loop(sc->mlx);
	}
}

void		graphical_shutdown(t_scene *scene)
{
	ctrl_shutdown(scene);
	if (scene->mlx)
	{
		screen_shutdown(scene);
		textures_unload(scene);
		free(scene->mlx);
	}
	doors_shutdown(scene);
	items_shutdown(scene);
	sprites_shutdown(scene);
	walls_shutdown(scene);
	physics_shutdown(&(scene->map));
	scene_shutdown(scene);
}

void		graphical_run(t_scene *scene)
{
	graphical_init(scene);
	graphical_main(scene);
	graphical_shutdown(scene);
}
