/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 22:36:49 by badam             #+#    #+#             */
/*   Updated: 2020/07/23 15:18:19 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*gna(char **line, bool is_first)
{
	if (!is_first)
		while (**line && !ft_isspace(**line) && **line != ',')
			(*line)++;
	while (**line && (ft_isspace(**line) || **line == ','))
		(*line)++;
	return (*line);
}

void	parse_color(char *colorstr, t_color *out, char *cmd, t_scene *scene)
{
	char	*red;
	char	*green;
	char	*blue;

	red = colorstr;
	green = gna(&colorstr, false);
	blue = gna(&colorstr, false);
	if (green == blue && ft_strlen(blue) == 0)
	{
		out->red = atoi(red);
		out->green = out->red;
		out->blue = out->red;
	}
	else if (ft_strlen(green) != 0 && ft_strlen(blue) != 0)
	{
		out->red = atoi(red);
		out->green = atoi(green);
		out->blue = atoi(blue);
	}
	else
		error(scene, ERR_INV_CONFIG, cmd);
}

char	*parse_texture(char *str, char *cmd, t_scene *scene)
{
	if (ft_strlen(str) != 0)
		return (relative_to(scene->file, str, scene));
	else
		error(scene, ERR_INV_CONFIG, cmd);
	return (NULL);
}

void	parse_colortexture(char *str, t_colortexture *out,
		char *cmd, t_scene *scene)
{
	if (ft_strlen(str) == 0)
		error(scene, ERR_INV_CONFIG, cmd);
	if (ft_isdigit(*str))
	{
		parse_color(str, &(out->color), cmd, scene);
	}
	else
	{
		out->is_texture = true;
		out->texture.path = parse_texture(str, cmd, scene);
	}
}

void	parse_resolution(char *resstr, t_scene *scene)
{
	int	screen_w;
	int	screen_h;

	screen_w = ft_atoi(gna(&resstr, false));
	screen_h = ft_atoi(gna(&resstr, false));
	if (screen_w <= 0 || screen_h <= 0)
		error(scene, ERR_INV_CONFIG, "R");
	scene->screen_w = screen_w;
	scene->screen_h = screen_h;
}
