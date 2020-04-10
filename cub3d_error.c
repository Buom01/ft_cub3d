/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:04 by badam             #+#    #+#             */
/*   Updated: 2020/04/10 22:42:23 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static void	print_error(e_error error)
{
	if (error == ERR_NO_ARG)
		ft_putstr_fd("Usage: ./cub3d scene.cub [--save output]\n", STDERR);
	else if (error == ERR_MISSING_OUTPUT)
		ft_putstr_fd("--save need destination file\n", STDERR);
	else if (error == ERR_UNKNOWN_ARG)
		ft_putstr_fd("Unknown arg: ", STDERR);
	else if (error == ERR_SCENE_NOT_LOADED)
		ft_putstr_fd(
			"No scene was loaded. Is the cub file provided and complete?\n",
			STDERR);
	else if (error == ERR_OPENING_SCENE)
		ft_putstr_fd("Can't open scene: ", STDERR);
	else if (error == ERR_READING_SCENE)
		ft_putstr_fd("Error while reading scene: ", STDERR);
	else if (error == ERR_INV_CONFIG)
		ft_putstr_fd("Misformatted or inalid configuration command: ", STDERR);
	else if (error == ERR_MAP_MALLOC)
		ft_putstr_fd("Memory allocation failed while parsing map\n", STDERR);
	else if (error == ERR_MAP_UNKNOWN)
		ft_putstr_fd("Unknown map object: ", STDERR);
	else
		ft_putstr_fd("Unknown error\n", STDERR); 
}

void				error(e_error error, char* data)
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
	exit(1);
}
