/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 14:16:15 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 14:07:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_entity	rawchar_to_entity(char c, t_scene *scene)
{
	if (c == '0' || ft_isspace(c))
		return (MAP_AIR);
	else if (c == '1')
		return (MAP_WALL);
	else if (c == '2')
		return (MAP_OBJECT);
	else if (c == '3')
		return (MAP_FAKEWALL);
	else if (c == 'N')
		return (MAP_PLAYER_N);
	else if (c == 'S')
		return (MAP_PLAYER_S);
	else if (c == 'W')
		return (MAP_PLAYER_W);
	else if (c == 'E')
		return (MAP_PLAYER_E);
	else if (c == 'H')
		return (MAP_DOOR);
	else if (c == '#')
		return (MAP_GRIDDOOR);
	else if (c == 'F')
		return (MAP_KEY);
	else
		error(scene, ERR_MAP_UNKNOWN, ft_ctoa(c));
	return (MAP_AIR);
}

static void		parse_rawmap_line(t_map *map, char *line, size_t linen,
		t_scene *scene)
{
	t_entity	*mapline;
	size_t		pos;

	mapline = map->data + (linen * map->width);
	ft_memset(mapline, MAP_AIR, map->width);
	pos = 0;
	while (*line && pos < map->width)
	{
		*mapline = rawchar_to_entity(*line, scene);
		mapline++;
		line++;
		pos++;
	}
}

void			parse_rawmap_free(char **rawmap, t_scene *scene)
{
	t_map	*map;
	char	**rawmapcpy;
	size_t	current_line;

	map = &scene->map;
	map->width = map_find_longer_line(rawmap);
	map->height = map_find_textblock_height(rawmap);
	if (!(map->data = malloc(sizeof(t_entity) * map->width * map->height)))
	{
		freeup_textblock(rawmap);
		error(scene, ERR_MALLOC, NULL);
	}
	rawmapcpy = rawmap;
	current_line = 0;
	while (*rawmapcpy)
	{
		parse_rawmap_line(map, *rawmapcpy, current_line++, scene);
		free(*(rawmapcpy++));
	}
	free(rawmap);
}
