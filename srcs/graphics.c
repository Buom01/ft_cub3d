/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:24:50 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 23:02:20 by badam            ###   ########.fr       */
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

static void	do_update(t_scene *sc,
		t_surface **rendr_surfs_p, t_surface **lst_rendr_surf_p)
{
	t_state		*state;
	t_ray		ray;

	state = &(sc->state);
	if (!sc->save)
	{
		ctrl_update(sc, state);
		move_update(state);
		physics_apply(sc);
	}
	ray.origin = state->pos;
	direction_from_state(&(ray.direction), state->yaw, state->pitch);
	walls_update(sc, ray, lst_rendr_surf_p, rendr_surfs_p);
	sprites_update(sc, state, ray, lst_rendr_surf_p);
	items_update(sc, state, ray, lst_rendr_surf_p);
	doors_update(sc, ray, lst_rendr_surf_p);
	raytr_render(sc, rendr_surfs_p, ray, state);
}

int			graphical_update(t_scene *sc)
{
	t_surface	*rendr_surfs;
	t_surface	*lst_rendr_surf;

	mlx_do_sync(sc->mlx);
	if (sc->paused || sc->loaded == false)
		return (0);
	rendr_surfs = NULL;
	lst_rendr_surf = NULL;
	do_update(sc, &rendr_surfs, &lst_rendr_surf);
	free_surfaces(rendr_surfs);
	return (0);
}

void		graphical_shutdown(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->mlx)
	{
		ctrl_shutdown(scene);
		screen_shutdown(scene);
		textures_unload(scene);
		free(scene->mlx);
		scene->mlx = NULL;
	}
	raytr_shutdown(scene);
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
	if (scene->save)
		graphical_update(scene);
	else
	{
		mlx_hook(scene->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
			main_stopall, scene);
		mlx_hook(scene->window, BUTTONPRESS, BUTTONPRESSMASK,
			window_clicked, scene);
		mlx_hook(scene->window, FOCUSIN, FOCUSCHANGEMASK,
			window_focus_in, scene);
		mlx_hook(scene->window, FOCUSOUT, FOCUSCHANGEMASK,
			window_focus_out, scene);
		mlx_hook(scene->window, ENTERNOTIFY, ENTERWINDOWMASK,
			window_mouse_in, scene);
		mlx_hook(scene->window, LEAVENOTIFY, LEAVEWINDOWMASK,
			window_mouse_out, scene);
		mlx_loop_hook(scene->mlx, graphical_update, scene);
		mlx_loop(scene->mlx);
	}
	graphical_shutdown(scene);
}
