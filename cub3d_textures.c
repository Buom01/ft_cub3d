/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 00:25:30 by badam             #+#    #+#             */
/*   Updated: 2020/05/08 17:09:03 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loadtexture(t_texture *texture, void *mlx)
{
	int	size;

	size = TEXTURE_SIZE;
	if (!texture->path || texture->data)
		return;
	if (!(texture->data =
			mlx_xpm_file_to_image(mlx, texture->path, &size, &size)))
		error(ERR_MLX_TEXTURE, texture->path);
}

static void	unloadtexture(t_texture *texture, void *mlx)
{
	if (!texture->data)
		return;
	mlx_destroy_image(mlx, texture->data);
}

void	textures_load(t_scene *scene)
{
	loadtexture(&scene->north, scene->mlx);
	loadtexture(&scene->south, scene->mlx);
	loadtexture(&scene->west, scene->mlx);
	loadtexture(&scene->east, scene->mlx);
	loadtexture(&scene->sprite, scene->mlx);
}

void	textures_unload(t_scene *scene)
{
	unloadtexture(&scene->north, scene->mlx);
	unloadtexture(&scene->south, scene->mlx);
	unloadtexture(&scene->west, scene->mlx);
	unloadtexture(&scene->east, scene->mlx);
	unloadtexture(&scene->sprite, scene->mlx);
}
