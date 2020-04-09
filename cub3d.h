/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 05:08:08 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# include "libft.h"
# include "gnl/get_next_line_bonus.h"


typedef unsigned char	t_byte;
typedef	char			*t_texture;
typedef t_byte			t_color[3];

typedef enum
{
	MAP_AIR = 0,
	MAP_WALL,
	MAP_OBJECT,
	MAP_PLAYER_N,
	MAP_PLAYER_S,
	MAP_PLAYER_W,
	MAP_PLAYER_E,

	MAX_ENTITY
}						e_entity;			

typedef struct			s_map
{
	e_entity			*data;
	size_t				size;
}						t_map;

typedef struct			s_scene
{
	bool				loaded;

	int					screen_w;
	int					screen_h;

	t_texture			north;
	t_texture			south;
	t_texture			west;
	t_texture			east;
	t_texture			sprite;

	t_color				floor;
	t_color				ceil;

	t_map				map;

	char				*save;
}						t_scene;

typedef enum
{
	ERR_NO_ARG,
	ERR_MISSING_OUTPUT,
	ERR_UNKNOWN_ARG,
	ERR_SCENE_NOT_LOADED,
	ERR_OPENING_SCENE,
	ERR_READING_SCENE,
	ERR_INV_CONFIG
}						e_error;


void					error(e_error error, char* data);

bool					has_extension(char *path, char *ext);

void					scene_defaults(t_scene *scene);
bool					validate_scene(t_scene *scene);

void					parse_scene(char *path, t_scene *scene);

void					parse_rawmap(char **rawmap, t_scene *scene);

#endif
