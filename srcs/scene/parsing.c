/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 01:14:43 by badam             #+#    #+#             */
/*   Updated: 2020/06/18 03:38:39 by badam            ###   ########.fr       */
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

static void	parse_color(char *colorstr, t_color *out, char *cmd, t_scene *scene)
{
	char	*red;
	char	*green;
	char	*blue;

	red = colorstr;
	green = gna(&colorstr, false);
	blue = gna(&colorstr, false);
	if (ft_strlen(red) == 0)
		error(scene, ERR_INV_CONFIG, cmd);
	if (green == blue || ft_strlen(blue) == 0)
	{
		out->red = atoi(red);
		out->green = out->red;
		out->blue = out->red;
	}
	else
	{
		out->red = atoi(red);
		out->green = atoi(green);
		out->blue = atoi(blue);
	}
}

static void	parse_resolution(char *resstr, t_scene *scene)
{
	scene->screen_w = ft_atoi(gna(&resstr, false));
	scene->screen_h = ft_atoi(gna(&resstr, false));
}

bool		parse_line(char *line, t_scene *scene, char *scfile)
{
	if (ft_strlen(gna(&line, true)) == 0)
		return (false);
	else if (ft_strnstr(line, "R", 1))
		parse_resolution(line, scene);
	else if (ft_strnstr(line, "NO", 2))
		scene->north.path = relative_to(scfile, gna(&line, false), scene);
	else if (ft_strnstr(line, "SO", 2))
		scene->south.path = relative_to(scfile, gna(&line, false), scene);
	else if (ft_strnstr(line, "WE", 2))
		scene->west.path = relative_to(scfile, gna(&line, false), scene);
	else if (ft_strnstr(line, "EA", 2))
		scene->east.path = relative_to(scfile, gna(&line, false), scene);
	else if (ft_strnstr(line, "S", 1))
		scene->sprite.path = relative_to(scfile, gna(&line, false), scene);
	else if (ft_strnstr(line, "F", 1))
		parse_color(gna(&line, false), &(scene->floor), "F", scene);
	else if (ft_strnstr(line, "C", 1))
		parse_color(gna(&line, false), &(scene->ceil), "C", scene);
	else if (ft_isdigit(*line))
		return (true);
	else
		error(scene, ERR_INV_CONFIG, line);
	return (false);
}