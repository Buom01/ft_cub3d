/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 17:45:22 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 02:51:04 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_args(int argc, char **argv, int *argi, t_scene *scene)
{
	if (!ft_strcmp(argv[*argi], "--save"))
	{
		if (*argi + 1 == argc)
			return (error(ERR_MISSING_OUTPUT, NULL));
		scene->save = ft_strdup(argv[++(*argi)]);
	}
	else if (has_extension(argv[*argi], ".cub"))
		return (parse_scene(argv[*argi], scene));
	else
		return (error(ERR_UNKNOWN_ARG, argv[*argi]));
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene scene;
	int		argi;

	if (argc < 2)
		return (error(ERR_NO_ARG, NULL));
	argi = 1;
	ft_memset(&scene, 0, sizeof(scene));
	while (argi < argc)
	{
		if (parse_args(argc, argv, &argi, &scene))
			return (1);
		argi++;
	}
	if (!scene.loaded)
		return (error(ERR_SCENE_NOT_LOADED, NULL));
	return (0);
}
