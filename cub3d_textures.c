/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 00:25:30 by badam             #+#    #+#             */
/*   Updated: 2020/04/14 00:51:28 by badam            ###   ########.fr       */
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
	if (texture->data)
		return;
	mlx_destroy_image(mlx, texture->data);
}

void	textures_load(t_scene *scene, void *mlx)
{
	loadtexture(&scene->north, mlx);
	loadtexture(&scene->south, mlx);
	loadtexture(&scene->west, mlx);
	loadtexture(&scene->east, mlx);
	loadtexture(&scene->sprite, mlx);
}

void	textures_unload(t_scene *scene, void *mlx)
{
	unloadtexture(&scene->north, mlx);
	unloadtexture(&scene->south, mlx);
	unloadtexture(&scene->west, mlx);
	unloadtexture(&scene->east, mlx);
	unloadtexture(&scene->sprite, mlx);
}
