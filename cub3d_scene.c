/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:40:12 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 05:16:48 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*gna(char **line, bool is_first)
{
	if (!is_first)
		while (**line && !ft_isspace(**line) && **line != ',')
			(*line)++;
	while (**line && (ft_isspace(**line) || **line == ','))
		(*line)++;
	return (*line);
}

static bool	parse_color(char *colorstr, t_color *out, char *cmd)
{
	char	*red;
	char	*green;
	char	*blue;

	red = colorstr;
	green = gna(&colorstr, false);
	blue = gna(&colorstr, false);
	if (ft_strlen(red) == 0)
		error(ERR_INV_CONFIG, cmd);
	if (green == blue || ft_strlen(blue) == 0)
	{
		out[0] = atoi(red);
		out[1] = out[0];
		out[2] = out[0];
	}
	else
	{
		out[0] = atoi(red);
		out[1] = atoi(green);
		out[2] = atoi(blue);
	}
}

static bool	parse_line(char	*line, t_scene *scene)
{
	if (ft_strlen(gna(&line, true)) == 0)
		return true;
	if (!(ft_strcmp(line, "R")))
	{
		scene->screen_w = ft_atoi(gna(&line, false));
		scene->screen_h = ft_atoi(gna(&line, false));
	}
	else if (!(ft_strcmp(line, "NO")))
		scene->north = ft_strdup( gna(&line, false) );
	else if (!(ft_strcmp(line, "SO")))
		scene->south = ft_strdup( gna(&line, false) );
	else if (!(ft_strcmp(line, "WE")))
		scene->west = ft_strdup( gna(&line, false) );
	else if (!(ft_strcmp(line, "EA")))
		scene->east = ft_strdup( gna(&line, false) );
	else if (!(ft_strcmp(line, "S")))
		scene->sprite = ft_strdup( gna(&line, false) );
	else if (!(ft_strcmp(line, "F")))
		parse_color( gna(&line, false), scene->floor, "F" );
	else if (!(ft_strcmp(line, "C")))
		parse_color( gna(&line, false), scene->ceil, "C" );
	else if (ft_isnum(line))
		return false;
	else
		error(ERR_INV_CONFIG, line);
	return true;
}

void		save_line(char *line, char ***textblock)
{
	if (!(*textblock))
		// first malloc and directly add text
	else
		// ft_realloc
}

void		parse_scene(char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl_result;
	bool	is_map;
	char	**rawmap;

	is_map = false;
	rawmap = NULL;
	scene_defaults(scene);
	if ((fd = open(path, O_RDONLY)) == -1)
		error(ERR_OPENING_SCENE, path);
	while ((gnl_result = get_next_line(fd, &line)) == 1)
	{
		if (is_map || (is_map = parse_line(line, scene)))
			save_line(line, &rawmap);
		else
			free(line);
	}
	close(fd);
	if (gnl_result == -1)
		error(ERR_READING_SCENE, path);
	parse_rawmap(rawmap, scene);
	scene->loaded = validate_scene(scene);
}
