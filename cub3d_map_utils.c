/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:08:39 by badam             #+#    #+#             */
/*   Updated: 2020/06/05 01:28:18 by badam            ###   ########.fr       */
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
	while (*(rawmap + height++))
		;
	return (height);
}

t_pos	i2pos(t_map *map, size_t i, t_direction dir)
{
	t_pos	pos;
	
	pos.y = 0.5;
	pos.z = (int)(i / map->width);
	pos.x = (int)(i - (map->width * pos.z));
	if (dir == DIR_NORTH)
		pos.x -= 0.5;
	if (dir == DIR_SOUTH)
		pos.x += 0.5;
	if (dir == DIR_WEST)
		pos.z -= 0.5;
	if (dir == DIR_EAST)
		pos.z += 0.5;
	return (pos);
}

void	init_player(t_map *map, t_state *state)
{
	size_t		i;
	t_entity	player;

	i = 0;
	while ((map->data[i] < MAP_PLAYER_N || map->data[i] > MAP_PLAYER_E)
			&& i < map->length)
		i++;
	if (i == map->length)
		error(ERR_MAP_UNKNOWN, NULL);
	map->init_player_pos = i;
	player = map->data[i];
	state->pos = i2pos(map, i, DIR_NONE);
	if (player == MAP_PLAYER_S)
		state->yaw = 180;
	else if (player == MAP_PLAYER_E)
		state->yaw = -90;
	else if (player == MAP_PLAYER_W)
		state->yaw = 90;
}
