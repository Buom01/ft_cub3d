/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 05:06:05 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 18:33:02 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool					validate_map(t_scene *scene)
{
	if (!scene->map.data)
		return (false);
	scene->map.length = scene->map.width * scene->map.height;
	init_player(&scene->map, &scene->state);
	physics_init(&scene->map);
	// create_walls()
	return (true);
}

inline static t_entity	rawchar_to_entity(char c)
{
	if (c == '0' || ft_isspace(c))
		return (MAP_AIR);
	else if (c == '1')
		return (MAP_WALL);
	else if (c == '2')
		return (MAP_OBJECT);
	else if (c == 'N')
		return (MAP_PLAYER_N);
	else if (c == 'S')
		return (MAP_PLAYER_S);
	else if (c == 'W')
		return (MAP_PLAYER_W);
	else if (c == 'E')
		return (MAP_PLAYER_E);
	else
	{
		error(ERR_MAP_UNKNOWN, ft_ctoa(c));
		return (MAP_AIR);
	}
}

void					parse_rawmap_line(t_map *map, char *line, size_t linen)
{
	t_entity	*mapline;
	size_t		pos;

	mapline = map->data + (linen * map->width);
	ft_memset(mapline, MAP_AIR, map->width);
	pos = 0;
	while (*line && pos < map->width)
	{
		*mapline = rawchar_to_entity(*line);
		mapline++;
		line++;
		pos++;
	}
}

void					parse_rawmap_free(char **rawmap, t_scene *scene)
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
		error(ERR_MAP_MALLOC, NULL);
	}
	rawmapcpy = rawmap;
	current_line = 0;
	while (*rawmapcpy)
	{
		parse_rawmap_line(map, *rawmapcpy, current_line++);
		free(*(rawmapcpy++));
	}
	free(rawmap);
}
