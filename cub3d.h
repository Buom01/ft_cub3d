/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 23:25:29 by badam            ###   ########.fr       */
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
# include <math.h>

# include "libft.h"
# include "gnl/get_next_line_bonus.h"

#include "cub3d_mlx.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define SIN sin
# define COS cos
# define PI 3.14159265
# define TORAD 3.14159265 / 180

# define TITLE "Buom_01's Cub3D"
# define TEXTURE_SIZE 64
# define FOV 90
# define MAX_DISTANCE 10
				
typedef unsigned char	t_byte;
typedef t_byte			t_color[3];

typedef	struct			s_texture
{
	char				*path;
	void				*data;
	int					*colors;
}						t_texture;

typedef struct			s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef t_vec			t_pos;

typedef double			t_angle;

typedef struct			s_base
{
	t_vec				u;
	t_vec				v;
	t_vec				n;
}						t_base;

typedef enum
{
	DIR_NONE,
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST
}	t_direction;

typedef enum
{
	KEY_UNKNOWN,
	KEY_ESC,
	KEY_LSHIFT,
	KEY_LCTRL,
	KEY_F10,
	KEY_F11,
	KEY_SPACE,
	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_LEFT,
	MAX_KEYS
}	t_key;

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
	size_t				init_player_pos;
}						t_map;

typedef struct			s_surf_cache
{
	double				n_dot_o_tr;
	t_vec				o_tr_cross_v;
	t_vec				u_cross_o_tr;
}						t_surf_cache;

typedef struct			s_surface
{
	t_pos				pos;
	t_angle				yaw;
	t_texture			*texture;
	double				distance;
	t_base				base;
	t_vec				o_t;
	t_surf_cache		cache;
	void				*next;
}						t_surface;

typedef struct			s_state
{
	t_pos				pos;
	t_angle				yaw;
	t_angle				pitch;
	bool				jumping;
	double				jump_velocity;
	bool				crouch;
	bool				keyboard[MAX_KEYS];
	double				mouse_x;
	double				mouse_y;
}						t_state;

typedef struct			s_scene
{
	bool				loaded;

	int					screen_w;
	int					screen_h;
	double				fov;
	double				vfov;

	void				*mlx;
	void				*window;
	double				*x2yaw;
	double				*y2pitch;
	void				*frame;
	int					*frame_colors;

	t_texture			north;
	t_texture			south;
	t_texture			west;
	t_texture			east;
	t_texture			sprite;

	t_color				floor;
	t_color				ceil;
	int					x_floor;
	int					x_ceil;

	t_map				map;
	t_state				state;
	t_surface			*surfaces;

	char				*save;
}						t_scene;

typedef struct
{
	t_pos				origin;
	t_vec				direction;
}						t_ray;

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

t_key					cub3d_mlx_tokey(t_syskey keycode);

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
t_pos					i2pos(t_map *map, size_t i, t_direction dir);
void					init_player(t_map *map, t_state *state);
void					physics_init(t_map *map);
bool					validate_map(t_scene *scene);

double					dist_2d(t_vec a, t_vec b);
void					vec_from_angles(t_vec *vec, t_angle yaw, t_angle pitch);
double					dot_product(t_vec a, t_vec b);
t_vec					cross_product(t_vec a, t_vec b);
t_vec					vec_diff(t_vec a, t_vec b);

void					raytr_init(t_scene *scene);
void					raytr_shutdown(t_scene *scene);
void					raytr_render(const t_scene *sc, const t_state *state,
							int w, int h);
void					raytr_free_surfs(t_surface *surf);
void					raytr_get_surfaces(const t_scene *scene,
							t_surface **surfs, t_pos rayorigin);
void					update_surface(t_surface *surf);
void					surfaces_sort(t_surface **surfs);

void					graphical_run(t_scene *scene);
int						ctrl_keypress(t_syskey keycode, t_state *state);
int						ctrl_keyrelease(t_syskey keycode, t_state *state);
void					ctrl_update(t_state *state);
void					ctrl_releaseall(t_state *state);
void					move_forward(t_state *state, int direction);
void					move_side(t_state *state, int direction);
void					jump(t_state *state);
void					move_update(t_state *state);

void					textures_load(t_scene *scene);
void					textures_unload(t_scene *scene);
int						get_texture_color_at(double x, double y, const int *colors);
int						*get_texture_color(int x, int y, int w, int *colors);
void					set_texture_color(int x, int y, int w,
							int *colors, int color);
int						to_x_color(t_color color);

#endif
