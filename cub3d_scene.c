/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:40:12 by badam             #+#    #+#             */
/*   Updated: 2020/04/10 22:10:23 by badam            ###   ########.fr       */
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

static void	parse_color(char *colorstr, t_color out, char *cmd)
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
		return false;
	if (!(ft_strnstr(line, "R", 1)))
	{
		scene->screen_w = ft_atoi(gna(&line, false));
		scene->screen_h = ft_atoi(gna(&line, false));
	}
	else if (!(ft_strnstr(line, "NO", 2)))
		scene->north = ft_strdup( gna(&line, false) );
	else if (!(ft_strnstr(line, "SO", 2)))
		scene->south = ft_strdup( gna(&line, false) );
	else if (!(ft_strnstr(line, "WE", 2)))
		scene->west = ft_strdup( gna(&line, false) );
	else if (!(ft_strnstr(line, "EA", 2)))
		scene->east = ft_strdup( gna(&line, false) );
	else if (!(ft_strnstr(line, "S", 1)))
		scene->sprite = ft_strdup( gna(&line, false) );
	else if (!(ft_strnstr(line, "F", 1)))
		parse_color( gna(&line, false), scene->floor, "F" );
	else if (!(ft_strnstr(line, "C", 1)))
		parse_color( gna(&line, false), scene->ceil, "C" );
	else if (ft_isdigit(*line))
		return true;
	else
		error(ERR_INV_CONFIG, line);
	return false;
}

void		save_line(char *line, char ***textblock)
{
	char	**textblockline;
	char	**newtextblock;
	size_t	lines;

	lines = 0;
	if (!(*textblock))
	{
		if ( !(*textblock = malloc(sizeof(char**) * 2)) )
			error(ERR_MAP_MALLOC, NULL);
	}		
	else
	{
		textblockline = *textblock;
		while (textblockline + lines)
			lines++;
		newtextblock = ft_realloc( (void*)(*textblock),
						sizeof(char**) * (lines + 1),
						sizeof(char**) * lines );
		if (newtextblock == NULL)
		{
			freeup_textblock(*textblock);
			error(ERR_MAP_MALLOC, NULL);
		}
		*textblock = newtextblock;
	}
	textblockline = *textblock + lines;
	*textblockline = line;
	*(textblockline + 1) = NULL;
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
	if (is_map)
	{
		parse_rawmap_free(rawmap, scene);
		scene->loaded = validate_scene(scene);
	}
}
