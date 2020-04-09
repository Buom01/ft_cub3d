/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:45:04 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 04:17:23 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "macro.h"

inline static void	print_error(e_error error)
{
	if (error == ERR_NO_ARG)
		PRINT(STDERR_FILENO, "Usage: ./cub3d scene.cub [--save output]\n");
	else if (error == ERR_MISSING_OUTPUT)
		PRINT(STDERR_FILENO, "--save need destination file\n");
	else if (error == ERR_UNKNOWN_ARG)
		PRINT(STDERR_FILENO, "Unknown arg: ");
	else if (error == ERR_SCENE_NOT_LOADED)
		PRINT(STDERR_FILENO,
			"No scene was loaded. Is the cub file provided and complete?\n");
	else if (error == ERR_OPENING_SCENE)
		PRINT(STDERR_FILENO, "Can't open scene: ");
	else if (error == ERR_READING_SCENE)
		PRINT(STDERR_FILENO, "Error while reading scene: ");
	else if (error == ERR_INV_CONFIG)
		PRINT(STDERR_FILENO, "Misformatted or inalid configuration command: ");
	else
		PRINT(STDERR_FILENO, "Unknown error\n"); 
}

void				error(e_error error, char* data)
{
	PRINT(STDERR_FILENO, "Error\n");
	print_error(error);
	if (data)
	{
		if (errno)
			perror(data);
		else
		{
			while (*data)
				PRINTCHAR(STDERR_FILENO, *(data++));
			PRINT(STDERR_FILENO, "\n");
		}
	} 
	exit(1);
}
