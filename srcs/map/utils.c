/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:08:39 by badam             #+#    #+#             */
/*   Updated: 2020/07/23 15:09:46 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		map_find_longer_line(char **rawmap)
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

size_t		map_find_textblock_height(char **rawmap)
{
	size_t	height;

	height = 0;
	while (*(rawmap + height))
		++height;
	return (height);
}

t_pos		i2pos(const t_map *map, size_t i, t_direction dir)
{
	t_pos	pos;

	pos.y = 0.5;
	pos.z = (int)(i / map->width);
	pos.x = (int)(i - (map->width * pos.z));
	if (dir == DIR_NORTH)
		pos.z -= 0.5;
	if (dir == DIR_SOUTH)
		pos.z += 0.5;
	if (dir == DIR_WEST)
		pos.x -= 0.5;
	if (dir == DIR_EAST)
		pos.x += 0.5;
	return (pos);
}

long long	pos2i(const t_map *map, t_pos pos)
{
	long long	i;

	i = roundl(pos.z) * map->width + roundl(pos.x);
	if (i < 0 || i >= (long long)map->length)
		return (-1);
	return (i);
}

void		init_player(t_map *map, t_scene *scene)
{
	size_t		i;
	t_entity	player;
	t_state		*state;

	state = &(scene->state);
	i = 0;
	while ((map->data[i] < MAP_PLAYER_N || map->data[i] > MAP_PLAYER_E)
			&& i < map->length)
		i++;
	if (i == map->length)
		error(scene, ERR_MAP, NULL);
	map->init_player_pos = i;
	player = map->data[i];
	state->pos = i2pos(map, i, DIR_NONE);
	if (player == MAP_PLAYER_S)
		state->yaw = PI;
	else if (player == MAP_PLAYER_E)
		state->yaw = PI / 2;
	else if (player == MAP_PLAYER_W)
		state->yaw = -PI / 2;
}
