/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 00:25:30 by badam             #+#    #+#             */
/*   Updated: 2020/07/21 14:38:24 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loadtexture(t_texture *texture, void *mlx, t_scene *scene)
{
	int		mock;
	char	*alternative_path;

	if (!texture->path || texture->data)
		return ;
	if (!has_extension(texture->path, ".xpm"))
	{
		alternative_path = ft_strjoin(texture->path, ".xpm");
		free(texture->path);
		texture->path = alternative_path;
	}
	texture->data = mlx_xpm_file_to_image(mlx, texture->path,
			&(texture->width), &(texture->height));
	if (!(texture->data))
		error(scene, ERR_MLX_TEXTURE, texture->path);
	texture->colors = (int*)mlx_get_data_addr(texture->data,
			&mock, &mock, &mock);
}

static void	unloadtexture(t_texture *texture, void *mlx)
{
	if (!texture->data)
		return ;
	mlx_destroy_image(mlx, texture->data);
	texture->data = NULL;
	texture->colors = NULL;
	free(texture->path);
	texture->path = NULL;
}

void		textures_load(t_scene *scene)
{
	void	*mlx;

	mlx = scene->mlx;
	loadtexture(&scene->north, mlx, scene);
	loadtexture(&scene->south, mlx, scene);
	loadtexture(&scene->west, mlx, scene);
	loadtexture(&scene->east, mlx, scene);
	if (scene->floor.is_texture)
		loadtexture(&(scene->floor.texture), mlx, scene);
	if (scene->ceil.is_texture)
		loadtexture(&(scene->ceil.texture), mlx, scene);
	loadtexture(&scene->sprite, mlx, scene);
	loadtexture(&scene->pane, mlx, scene);
	loadtexture(&scene->door_a, mlx, scene);
	loadtexture(&scene->door_b, mlx, scene);
	loadtexture(&scene->door_grid, mlx, scene);
	loadtexture(&scene->key, mlx, scene);
	loadtexture(&scene->treasure, mlx, scene);
}

void		textures_unload(t_scene *scene)
{
	void	*mlx;

	mlx = scene->mlx;
	unloadtexture(&scene->north, mlx);
	unloadtexture(&scene->south, mlx);
	unloadtexture(&scene->west, mlx);
	unloadtexture(&scene->east, mlx);
	if (scene->floor.is_texture)
		unloadtexture(&(scene->floor.texture), mlx);
	if (scene->ceil.is_texture)
		unloadtexture(&(scene->ceil.texture), mlx);
	unloadtexture(&scene->sprite, mlx);
	unloadtexture(&scene->pane, mlx);
	unloadtexture(&scene->door_b, mlx);
	unloadtexture(&scene->door_a, mlx);
	unloadtexture(&scene->door_grid, mlx);
	unloadtexture(&scene->key, mlx);
	unloadtexture(&scene->treasure, mlx);
}
