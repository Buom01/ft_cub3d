/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/07/02 22:54:17 by badam            ###   ########.fr       */
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

# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line_bonus.h"

# include "mlx/cub3d_mlx.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define SIN sin
# define COS cos
# define PI acos(-1.0)
# define TORAD PI / 180.0
# define TODEG 180.0 / PI

# define TITLE "Buom_01's Cub3D"
# define TEXTURE_SIZE 64
# define FOV 90
				
typedef unsigned char	t_byte;

typedef struct			s_color
{
	t_byte				alpha;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
}						t_color;

typedef	struct			s_texture
{
	char				*path;
	void				*data;
	int					*colors;
}						t_texture;

typedef	struct			s_colortexture
{
	bool				is_texture;
	t_color				color;
	t_texture			texture;
}						t_colortexture;

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
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
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
	MAP_FAKEWALL,
	MAP_PLAYER_N,
	MAP_PLAYER_S,
	MAP_PLAYER_W,
	MAP_PLAYER_E,
	MAP_OBJECT,
	MAP_DOOR,
	MAP_GRIDDOOR,
	MAP_KEY
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
	double				distance;
	double				n_dot_o_tr;
	t_vec				o_tr_cross_v;
	t_vec				u_cross_o_tr;
}						t_surf_cache;

typedef struct			s_surface
{
	t_pos				pos;
	t_angle				yaw;
	t_texture			*texture;
	t_base				base;
	t_vec				o_t;
	t_surf_cache		cache;
	void				*next;
}						t_surface;

typedef struct			s_sprite
{
	t_pos				pos;
	t_texture			*texture;
	void				*next;
}						t_sprite;
	bool				facing;

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
	int					mouse_origin_x;
	int					mouse_origin_y;

	double				shadow;
	double				shadow_fade;
	double				shadow_begin;
	bool				noclip;

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
	t_texture			door;
	t_texture			griddoor;
	t_texture			key;

	t_colortexture		floor;
	t_colortexture		ceil;
	int					x_floor;
	int					x_ceil;

	t_map				map;
	t_state				state;
	t_surface			*surfaces;
	t_sprite			*sprites;

	char				*save;
}						t_scene;

typedef struct
{
	t_pos				origin;
	t_vec				direction;
}						t_ray;

typedef enum
{
	TR_NOT_HIT,
	TR_FLOOR,
	TR_HIT
}	t_raytrace_return;

typedef enum
{
	ERR_NO_ARG,
	ERR_MISSING_OUTPUT,
	ERR_UNKNOWN_ARG,
	ERR_MALLOC,
	ERR_SCENE_NOT_LOADED,
	ERR_OPENING_SCENE,
	ERR_READING_SCENE,
	ERR_INV_CONFIG,
	ERR_MAP_UNKNOWN,
	ERR_MLX_INIT,
	ERR_MLX_TEXTURE,
	ERR_MLX_UNKNOWN
}	t_error;

t_key					cub3d_mlx_tokey(t_syskey keycode);

void					error(t_scene *scene, t_error error, char *data);
void					main_shutdown(t_scene *scene);
void					freeup_textblock(char **textblock);
bool					has_extension(char *path, char *ext);
char					*relative_to(const char *file_from, const char *file,
							t_scene *scene);

void					scene_defaults(t_scene *scene);
bool					validate_scene(t_scene *scene);
char					*gna(char **line, bool is_first);
void					parse_scene(char *scenefile, t_scene *scene);
bool					parse_line(char *line, t_scene *scene, char *scfile);
void					parse_color(char *colorstr, t_color *out);
void					parse_colortexture(char *str, t_colortexture *out,
							char *scfile, char *cmd, t_scene *scene);
void					parse_resolution(char *resstr, t_scene *scene);
void					scene_shutdown(t_scene *scene);

size_t					map_find_longer_line(char **rawmap);
size_t					map_find_textblock_height(char **rawmap);
void					parse_rawmap_free(char **rawmap, t_scene *scene);
t_pos					i2pos(t_map *map, size_t i, t_direction dir);
void					init_player(t_map *map, t_scene *scene);
t_surface				*add_surface(t_surface **list, t_surface **last,
							t_scene *scene);
bool					is_surface_useful(t_surface *candidate,
							t_ray ray, t_angle yaw, t_scene *sc);
void					free_surfaces(t_surface *surf);

void					walls_init(t_scene *scene);
void					walls_update(t_scene *sc, t_state *state, t_ray ray,
							t_surface **lst_surf, t_surface **surfs);
void					walls_shutdown(t_scene *scene);
void					physics_init(t_map *map, t_scene *scene);
void					physics_shutdown(t_map *map);
bool					validate_map(t_scene *scene);

void					sprites_init(t_scene *scene);
void					sprites_update(t_scene *sc, t_state *state, t_ray ray,
							 t_surface **lst_surf);
void					sprites_shutdown(t_scene *scene);

double					fast_cos(double angle);
double					dist_2d(t_vec a, t_vec b);
t_angle					point_to(t_pos from, t_pos to);
void					vec_from_angles(t_vec *vec, t_angle yaw, t_angle pitch);
double					dot_product(t_vec a, t_vec b);
t_vec					cross_product(t_vec a, t_vec b);
t_vec					vec_diff(t_vec a, t_vec b);

void					raytr_init(t_scene *scene);
void					raytr_render(t_scene *sc, t_surface **surfs,
							t_ray ray, int w, int h);
void					add_render_surface(const t_surface *src,
							t_surface **lst, t_scene *scene);
void					update_surface(t_surface *surf);
void					surfaces_pre_tr(t_surface *surfs, t_pos origin);
void					surfaces_sort(t_surface **surfs);

void					graphical_run(t_scene *scene);
void					graphical_shutdown(t_scene *scene);
void					ctrl_init(t_scene *sc);
void					ctrl_update(t_scene *scene, t_state *state);
void					ctrl_shutdown(t_scene *scene);
int						ctrl_keypress(t_syskey keycode, t_state *state);
int						ctrl_keyrelease(t_syskey keycode, t_state *state);
void					ctrl_releaseall(t_state *state);
int						ctrl_mousemove(int x, int y, t_scene *sc);
void					move_forward(t_state *state, int direction);
void					move_side(t_state *state, int direction);
void					jump(t_state *state);
void					move_update(t_state *state);

void					textures_load(t_scene *scene);
void					textures_unload(t_scene *scene);
int						get_texture_color_at(double x, double y, const int *colors);
int						*get_texture_color(int x, int y, int w, int *colors);
int						to_x_color(t_color *color);
void					color_darken(int *color, double dark_ratio);
int						fade_color(int c1, int c2, double balance);

#endif
