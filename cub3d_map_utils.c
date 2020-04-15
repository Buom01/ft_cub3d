/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:08:39 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 01:30:04 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	map_find_longer_line(char **rawmap)
{
	size_t	longer;
	size_t	length;

	longer = 0;
	while (*rawmap)
	{
		length = ft_strlen(*rawmap);
		if (length > longer)
			longer = length;
		rawmap++;
	}
	return (longer);
}

size_t	map_find_textblock_height(char **rawmap)
{
	size_t	height;

	height = 0;
	while (*(*rawmap + height))
		height++;
	return (height);
}

size_t	map_get_player_pos(t_map *map)
{
	size_t		pos;
	
	pos = 0;
	while ((map->data[pos] < MAP_PLAYER_N || map->data[pos] > MAP_PLAYER_E)
			&& pos < map->length)
		pos++;
	if (pos == map->width * map->height)
		error(ERR_MAP_UNKNOWN, NULL);
	return (pos);
}

void	init_player(t_map *map, t_state *state)
{
	size_t		pos;
	t_entity	player;

	pos = map_get_player_pos(map);
	player = map->data[pos];
	state->pos.y = pos / map->width;
	state->pos.x = pos - (map->width * state->pos.y);
	if (player == MAP_PLAYER_S)
		state->yaw = 180;
	else if (player == MAP_PLAYER_E)
		state->yaw = 90;
	else if (player == MAP_PLAYER_W)
		state->yaw = -90;
}
