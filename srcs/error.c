/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:04 by badam             #+#    #+#             */
/*   Updated: 2020/07/26 16:15:10 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_extended_error(t_error error)
{
	if (error == ERR_MLX_TEXTURE)
		ft_putstr_fd("Texture failed to load: ", STDERR);
	else if (error == ERR_WRITEIMAGE)
		ft_putstr_fd("Error while creating image: ", STDERR);
	else
		ft_putstr_fd("Unknown error\n", STDERR);
}

static void	print_error(t_error error)
{
	if (error == ERR_NO_ARG)
		ft_putstr_fd("Usage: ./cub3d scene.cub [--save output]\n", STDERR);
	else if (error == ERR_UNKNOWN_ARG)
		ft_putstr_fd("Unknown arg: ", STDERR);
	else if (error == ERR_DOUBLE_SCENE)
		ft_putstr_fd("A scene were already loaded when loading: ", STDERR);
	else if (error == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed\n", STDERR);
	else if (error == ERR_SCENE_NOT_LOADED)
		ft_putstr_fd("No scene loaded. Is the cub file correct ?\n", STDERR);
	else if (error == ERR_OPENING_SCENE)
		ft_putstr_fd("Can't open scene: ", STDERR);
	else if (error == ERR_READING_SCENE)
		ft_putstr_fd("Error while reading scene: ", STDERR);
	else if (error == ERR_INV_CONFIG)
		ft_putstr_fd("Inalid or missing configuration command: ", STDERR);
	else if (error == ERR_MAP_UNKNOWN)
		ft_putstr_fd("Unknown map object: ", STDERR);
	else if (error == ERR_MAP)
		ft_putstr_fd("Invalid map\n", STDERR);
	else if (error == ERR_MLX_INIT)
		ft_putstr_fd("MiniLibX initialization failed\n", STDERR);
	else
		print_extended_error(error);
}

void		error(t_scene *scene, t_error error, char *data)
{
	ft_putstr_fd("Error\n", STDERR);
	print_error(error);
	if (data)
	{
		if (errno)
			perror(data);
		else
		{
			ft_putstr_fd(data, STDERR);
			ft_putchar_fd('\n', STDERR);
		}
	}
	if (scene)
	{
		graphical_shutdown(scene);
		main_shutdown(scene);
	}
	exit(EXIT_FAILURE);
}
