/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:45:22 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:55:24 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_args(int argc, char **argv, int *argi, t_scene *scene)
{
	if (!ft_strcmp(argv[*argi], "--save"))
	{
		if (*argi + 1 == argc)
			error(scene, ERR_MISSING_OUTPUT, NULL);
		scene->save = ft_strdup(argv[++(*argi)]);
	}
	else if (has_extension(argv[*argi], ".cub"))
		parse_scene(argv[*argi], scene);
	else
		error(scene, ERR_UNKNOWN_ARG, argv[*argi]);
}

void		main_shutdown(t_scene *scene)
{
	if (scene->save)
		free(scene->save);
}

int			main(int argc, char **argv)
{
	t_scene scene;
	int		argi;

	if (argc < 2)
		error(&scene, ERR_NO_ARG, NULL);
	argi = 1;
	ft_memset(&scene, 0, sizeof(scene));
	while (argi < argc)
	{
		parse_args(argc, argv, &argi, &scene);
		argi++;
	}
	if (!scene.loaded)
		error(&scene, ERR_SCENE_NOT_LOADED, NULL);
	graphical_run(&scene);
	main_shutdown(&scene);
	return (0);
}
