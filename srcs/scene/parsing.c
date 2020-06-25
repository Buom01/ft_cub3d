/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 01:14:43 by badam             #+#    #+#             */
/*   Updated: 2020/06/22 22:54:00 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parse_additionnal(char *line, t_scene *sc, char *scfile)
{
	if (ft_strnstr(line, "SHADOW", 6))
		sc->shadow = ft_atoi(gna(&line, false));
	else if (ft_strnstr(line, "shadow_fade", 11))
		sc->shadow_fade = ft_atoi(gna(&line, false));
	else if (ft_strnstr(line, "NOCLIP", 6))
		sc->noclip = true;
	else if (ft_strnstr(line, "DOOR", 4))
		sc->door.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "GRIDDOOR", 8))
		sc->griddoor.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "KEY", 3))
		sc->key.path = relative_to(scfile, gna(&line, false), sc);
	else
	{
		free(scfile);
		error(sc, ERR_INV_CONFIG, line);
	}
	return (false);
}

bool		parse_line(char *line, t_scene *sc, char *scfile)
{
	if (ft_strlen(gna(&line, true)) == 0)
		return (false);
	else if (ft_strnstr(line, "R", 1))
		parse_resolution(line, sc);
	else if (ft_strnstr(line, "NO", 2))
		sc->north.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "SO", 2))
		sc->south.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "WE", 2))
		sc->west.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "EA", 2))
		sc->east.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "S", 1))
		sc->sprite.path = relative_to(scfile, gna(&line, false), sc);
	else if (ft_strnstr(line, "F", 1))
		parse_colortexture(gna(&line, false), &(sc->floor), scfile, "F", sc);
	else if (ft_strnstr(line, "C", 1))
		parse_colortexture(gna(&line, false), &(sc->ceil), scfile, "C", sc);
	else if (ft_isdigit(*line))
		return (true);
	else
		return (parse_additionnal(line, sc, scfile));
	return (false);
}
