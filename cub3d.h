/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/04/15 02:41:33 by badam            ###   ########.fr       */
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
# include <mlx.h>

# include "libft.h"
# include "gnl/get_next_line_bonus.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define TEXTURE_SIZE 64

typedef unsigned char	t_byte;
typedef t_byte			t_color[3];

typedef	struct			s_texture
{
	char				*path;
	void				*data;
}						t_texture;

typedef struct			s_pos
{
	double				x;
	double				y;
	double				z;
}						t_pos;

typedef double			t_angle;

typedef enum
{
	MAP_AIR = 0,
	MAP_WALL,
	MAP_OBJECT,
	MAP_PLAYER_N,
	MAP_PLAYER_S,
	MAP_PLAYER_W,
	MAP_PLAYER_E
}	t_entity;

typedef struct			s_map
{
	t_entity			*data;
	bool				*walkable;
	size_t				width;
	size_t				height;
	size_t				length;
}						t_map;

typedef struct			s_state
{
	t_pos				pos;
	t_angle				yaw;
}						t_state;

typedef struct			s_surface
{
	t_pos				pos;
	t_angle				yaw;
	t_texture			*texture;
	void				*next;
}						t_surface;

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
	t_state				state;
	t_surface			*surfaces;

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
	ERR_INV_CONFIG,
	ERR_MAP_MALLOC,
	ERR_MAP_UNKNOWN,
	ERR_MLX_INIT,
	ERR_MLX_TEXTURE,
	ERR_MLX_UNKNOWN
}	t_error;

void					error(t_error error, char *data);
void					freeup_textblock(char **textblock);
bool					has_extension(char *path, char *ext);

void					scene_defaults(t_scene *scene);
bool					validate_scene(t_scene *scene);
void					parse_scene(char *path, t_scene *scene);
bool					parse_line(char *line, t_scene *scene);

size_t					map_find_longer_line(char **rawmap);
size_t					map_find_textblock_height(char **rawmap);
void					parse_rawmap_free(char **rawmap, t_scene *scene);
size_t					map_get_player_pos(t_map *map);
void					init_player(t_map *map, t_state *state);
void					physics_init(t_map *map);
bool					validate_map(t_scene *scene);

void					raytracing_init(t_scene *scene);

void					graphical_run(t_scene *scene);
void					textures_load(t_scene *scene, void *mlx);
void					textures_unload(t_scene *scene, void *mlx);

#endif
