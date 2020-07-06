/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 00:25:30 by badam             #+#    #+#             */
/*   Updated: 2020/07/06 18:09:52 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loadtexture(t_texture *texture, void *mlx, t_scene *scene)
{
	int		size;
	int		mock;
	char	*alternative_path;

	size = TEXTURE_SIZE;
	if (!texture->path || texture->data)
		return ;
	if (!(texture->data =
			mlx_xpm_file_to_image(mlx, texture->path, &size, &size)))
	{
		alternative_path = ft_strjoin(texture->path, ".xpm");
		if ((texture->data =
				mlx_xpm_file_to_image(mlx, alternative_path, &size, &size)))
		{
			free(texture->path);
			texture->path = alternative_path;
		}
		else
		{
			error(scene, ERR_MLX_TEXTURE, texture->path);
		}
	}
	texture->colors = (int*)mlx_get_data_addr(texture->data,
			&mock, &mock, &mock);
}

static void	unloadtexture(t_texture *texture, void *mlx)
{
	if (!texture->data)
		return ;
	mlx_destroy_image(mlx, texture->data);
	texture->colors = NULL;
}

void		textures_load(t_scene *scene)
{
	void	*mlx;

	mlx = scene->mlx;
	loadtexture(&scene->north, mlx, scene);
	loadtexture(&scene->south, mlx, scene);
	loadtexture(&scene->west, mlx, scene);
	loadtexture(&scene->east, mlx, scene);
	loadtexture(&scene->sprite, mlx, scene);
}

void		textures_unload(t_scene *scene)
{
	void	*mlx;

	mlx = scene->mlx;
	unloadtexture(&scene->north, mlx);
	unloadtexture(&scene->south, mlx);
	unloadtexture(&scene->west, mlx);
	unloadtexture(&scene->east, mlx);
	unloadtexture(&scene->sprite, mlx);
}
