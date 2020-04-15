/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scene_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 01:14:43 by badam             #+#    #+#             */
/*   Updated: 2020/04/14 00:35:23 by badam            ###   ########.fr       */
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

static void	parse_resolution(char *resstr, t_scene *scene)
{
	scene->screen_w = ft_atoi(gna(&resstr, false));
	scene->screen_h = ft_atoi(gna(&resstr, false));
}

bool		parse_line(char *line, t_scene *scene)
{
	if (ft_strlen(gna(&line, true)) == 0)
		return (false);
	else if (ft_strnstr(line, "R", 1))
		parse_resolution(line, scene);
	else if (ft_strnstr(line, "NO", 2))
		scene->north.path = ft_strdup(gna(&line, false));
	else if (ft_strnstr(line, "SO", 2))
		scene->south.path = ft_strdup(gna(&line, false));
	else if (ft_strnstr(line, "WE", 2))
		scene->west.path = ft_strdup(gna(&line, false));
	else if (ft_strnstr(line, "EA", 2))
		scene->east.path = ft_strdup(gna(&line, false));
	else if (ft_strnstr(line, "S", 1))
		scene->sprite.path = ft_strdup(gna(&line, false));
	else if (ft_strnstr(line, "F", 1))
		parse_color(gna(&line, false), scene->floor, "F");
	else if (ft_strnstr(line, "C", 1))
		parse_color(gna(&line, false), scene->ceil, "C");
	else if (ft_isdigit(*line))
		return (true);
	else
		error(ERR_INV_CONFIG, line);
	return (false);
}
