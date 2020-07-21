/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 01:14:43 by badam             #+#    #+#             */
/*   Updated: 2020/07/21 14:37:33 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_command(char *line, char *cmd)
{
	while (ft_isspace(*line) && *line != '\n' && *line)
		line++;
	while (*cmd && *line == *cmd)
	{
		line++;
		cmd++;
	}
	return (!*cmd && (ft_isspace(*line) || *line == '\n' || !*line));
}

static bool	parse_additionnal(char *line, t_scene *sc)
{
	if (is_command(line, "SHADOW"))
		sc->shadow = ft_atoi(gna(&line, false));
	else if (is_command(line, "SHADOW_FADE"))
		sc->shadow_fade = ft_atoi(gna(&line, false));
	else if (is_command(line, "NOCLIP"))
		sc->noclip = true;
	else if (is_command(line, "DOOR_A"))
		sc->door_a.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "DOOR_B"))
		sc->door_b.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "DOOR_GRID"))
		sc->door_grid.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "PANE"))
		sc->pane.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "KEY"))
		sc->key.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "TREASURE"))
		sc->treasure.path = relative_to(sc->file, gna(&line, false), sc);
	else
		error(sc, ERR_INV_CONFIG, line);
	return (false);
}

bool		parse_line(char *line, t_scene *sc)
{
	if (ft_strlen(gna(&line, true)) == 0)
		return (false);
	else if (is_command(line, "R"))
		parse_resolution(line, sc);
	else if (is_command(line, "NO"))
		sc->north.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "SO"))
		sc->south.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "WE"))
		sc->west.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "EA"))
		sc->east.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "S"))
		sc->sprite.path = relative_to(sc->file, gna(&line, false), sc);
	else if (is_command(line, "F"))
		parse_colortexture(gna(&line, false), &(sc->floor), "F", sc);
	else if (is_command(line, "C"))
		parse_colortexture(gna(&line, false), &(sc->ceil), "C", sc);
	else if (ft_isdigit(*line))
		return (true);
	else
		return (parse_additionnal(line, sc));
	return (false);
}
