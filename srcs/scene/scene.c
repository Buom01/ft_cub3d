/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:40:12 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:39:54 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	save_line(char *line, char ***textblock, t_scene *scene)
{
	char	**newtextblock;
	size_t	lines;

	lines = 0;
	if (!(*textblock))
	{
		if (!(*textblock = malloc(sizeof(char**) * 2)))
			error(scene, ERR_MALLOC, NULL);
	}
	else
	{
		while (*(*textblock + lines))
			lines++;
		newtextblock = ft_realloc((void*)(*textblock),
						sizeof(char**) * (lines + 2), sizeof(char**) * lines);
		if (newtextblock == NULL)
		{
			freeup_textblock(*textblock);
			error(scene, ERR_MALLOC, NULL);
		}
		*textblock = newtextblock;
	}
	*(*textblock + lines) = line;
	*(*textblock + lines + 1) = NULL;
}

void		parse_scene(char *scenefile, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl_result;
	bool	is_map;
	char	**rawmap;

	is_map = false;
	rawmap = NULL;
	scene_defaults(scene);
	if ((fd = open(scenefile, O_RDONLY)) == -1)
		error(scene, ERR_OPENING_SCENE, scenefile);
	while ((gnl_result = get_next_line(fd, &line)) == 1)
	{
		if (is_map || (is_map = parse_line(line, scene, scenefile)))
			save_line(line, &rawmap, scene);
		else
			free(line);
	}
	close(fd);
	if (gnl_result == -1)
		error(scene, ERR_READING_SCENE, scenefile);
	if (is_map)
		parse_rawmap_free(rawmap, scene);
	scene->loaded = validate_scene(scene);
}
