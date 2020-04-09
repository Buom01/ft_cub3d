/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 02:36:15 by badam            ###   ########.fr       */
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
	size_t				*linelen;
}						t_map;

typedef struct			s_scene
{
	bool				loaded;

	size_t				screen_w;
	size_t				screen_h;

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
	ERR_READING_SCENE
}						e_error;


int						error(e_error error, char* data);

bool					has_extension(char *path, char *ext);

int						parse_scene(char* path, t_scene *scene);

#endif
