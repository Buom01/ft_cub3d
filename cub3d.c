/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:45:22 by badam             #+#    #+#             */
/*   Updated: 2020/04/14 00:52:32 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	shutdown(t_scene *scene)
{
	free(scene->north.path);
	free(scene->south.path);
	free(scene->west.path);
	free(scene->east.path);
	free(scene->sprite.path);
	free(scene->map.data);
}

static void	parse_args(int argc, char **argv, int *argi, t_scene *scene)
{
	if (!ft_strcmp(argv[*argi], "--save"))
	{
		if (*argi + 1 == argc)
			error(ERR_MISSING_OUTPUT, NULL);
		scene->save = ft_strdup(argv[++(*argi)]);
	}
	else if (has_extension(argv[*argi], ".cub"))
		parse_scene(argv[*argi], scene);
	else
		error(ERR_UNKNOWN_ARG, argv[*argi]);
}

int			main(int argc, char **argv)
{
	t_scene scene;
	int		argi;

	if (argc < 2)
		error(ERR_NO_ARG, NULL);
	argi = 1;
	ft_memset(&scene, 0, sizeof(scene));
	while (argi < argc)
	{
		parse_args(argc, argv, &argi, &scene);
		argi++;
	}
	if (!scene.loaded)
		error(ERR_SCENE_NOT_LOADED, NULL);
	graphical_run(&scene);
	shutdown(&scene);
	return (0);
}
