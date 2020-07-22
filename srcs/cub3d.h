/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:57:53 by badam             #+#    #+#             */
/*   Updated: 2020/07/22 23:24:49 by badam            ###   ########.fr       */
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
# include "mlx/cub3d_mlx.h"

# include "libs/gnl/get_next_line_bonus.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define SIN sin
# define COS cos
# define PI 3.141592654
# define TORAD 0.01745329252
# define TODEG 57.29577951
# define EPSYLON 0.00000001

# define COLOR_ALPHA 4278190080
# define COLOR_VOID 16711935
# define TITLE "Buom_01's Cub3D"
# define FOV 70
# define PLAYER_RADIUS 0.20

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
	int					width;
	int					height;
	size_t				max_index;
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
	MAP_PANE,
	MAP_DOOR,
	MAP_DOOR_GRID,
	MAP_KEY,
	MAP_TREASURE
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
	bool				backface;
	double				special;
	double				crop_x;
	double				crop_y;
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

typedef enum
{
	ITEM_EMPTY = 0,
	ITEM_KEY,
	ITEM_TREASURE,
	MAX_ITEMS
}	t_itemtype;

typedef struct			s_item
{
	t_pos				pos;
	t_itemtype			type;
	t_texture			*texture;
	double				animation;
	void				*next;
}						t_item;

typedef enum
{
	DOOR_STANDARD,
	DOOR_GRID
}	t_doortype;

typedef struct			s_door
{
	t_pos				pos;
	bool				vertical;
	t_doortype			type;
	t_texture			*texture;
	t_texture			*texture_b;
	double				state;
	t_itemtype			key;
	size_t				physic_index;
	void				*next;
}						t_door;

typedef struct			s_state
{
	t_pos				pos;
	double				move_x;
	double				move_z;
	t_angle				yaw;
	t_angle				pitch;
	bool				jumping;
	double				jump_velocity;
	bool				crouch;
	bool				inventory[MAX_ITEMS];
	bool				keyboard[MAX_KEYS];
	double				mouse_x;
	double				mouse_y;
}						t_state;

typedef struct			s_scene
{
	bool				loaded;
	char				*file;
	bool				paused;
	bool				focused;
	bool				mouse_in;

	size_t				screen_w;
	size_t				screen_h;
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

	t_texture			door_a;
	t_texture			door_b;
	t_texture			door_grid;

	t_texture			pane;
	t_texture			key;
	t_texture			treasure;

	t_colortexture		floor;
	t_colortexture		ceil;
	int					x_floor;
	int					x_ceil;
	t_surface			floor_surf;
	t_surface			ceil_surf;

	t_map				map;
	t_state				state;
	t_surface			*surfaces;
	t_sprite			*sprites;
	t_item				*items;
	t_door				*doors;

	char				*save;
}						t_scene;

typedef struct			s_ray
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
	ERR_UNKNOWN_ARG,
	ERR_MALLOC,
	ERR_SCENE_NOT_LOADED,
	ERR_OPENING_SCENE,
	ERR_READING_SCENE,
	ERR_INV_CONFIG,
	ERR_MAP_UNKNOWN,
	ERR_MLX_INIT,
	ERR_MLX_TEXTURE,
	ERR_MLX_UNKNOWN,
	ERR_WRITEIMAGE,
	ERR_UNKNOWN
}	t_error;

typedef	struct			s_bmpheader
{
	t_byte				type[2];
	t_byte				total_size[4];
	t_byte				appli_1[2];
	t_byte				appli_2[2];
	t_byte				offset[4];
	t_byte				dib_size[4];
	t_byte				width[4];
	t_byte				height[4];
	t_byte				planes[2];
	t_byte				bpp[2];
	t_byte				compression[4];
	t_byte				bitmap_size[4];
	t_byte				v_print_res[4];
	t_byte				h_print_res[4];
	t_byte				palette_colors[4];
	t_byte				importants_colors[4];
}						t_bmpheader;

t_key					cub3d_mlx_tokey(t_syskey keycode);

void					error(t_scene *scene, t_error error, char *data);
void					main_shutdown(t_scene *scene);
int						main_stopall(t_scene *scene);
void					freeup_textblock(char **textblock);
bool					has_extension(char *path, char *ext);
char					*relative_to(const char *file_from, const char *file,
							t_scene *scene);

int						window_clicked(t_scene *scene);
int						window_focus_in(t_scene *scene);
int						window_focus_out(t_scene *scene);
int						window_mouse_in(t_scene *scene);
int						window_mouse_out(t_scene *scene);

void					scene_defaults(t_scene *scene);
bool					validate_scene(t_scene *scene);
char					*gna(char **line, bool is_first);
void					parse_scene(char *scenefile, t_scene *scene);
bool					parse_line(char *line, t_scene *scene);
void					parse_color(char *colorstr, t_color *out);
void					parse_colortexture(char *str, t_colortexture *out,
							char *cmd, t_scene *scene);
void					parse_resolution(char *resstr, t_scene *scene);
void					scene_set_pause(t_scene *scene, bool pause);
void					scene_shutdown(t_scene *scene);

size_t					map_find_longer_line(char **rawmap);
size_t					map_find_textblock_height(char **rawmap);
void					parse_rawmap_free(char **rawmap, t_scene *scene);
t_pos					i2pos(const t_map *map, size_t i, t_direction dir);
long long				pos2i(const t_map *map, t_pos pos);
void					init_player(t_map *map, t_scene *scene);
t_surface				*add_surface(t_surface **list, t_surface **last,
							t_scene *scene);
bool					is_surface_useful(t_surface *candidate,
							t_ray ray, t_angle yaw, t_scene *sc);
void					free_surfaces(t_surface *surfs);

void					walls_init(t_scene *scene, t_map *map);
void					walls_update(t_scene *sc, t_ray ray,
							t_surface **lst_surf, t_surface **surfs);
void					walls_shutdown(t_scene *scene);
void					physics_init(t_map *map, t_scene *scene);
void					physics_shutdown(t_map *map);
bool					validate_map(t_scene *scene);

void					fakewalls_init(t_scene *scene, t_map *map);

void					sprites_init(t_scene *scene, t_map *map);
void					sprites_update(t_scene *sc, t_state *state, t_ray ray,
							t_surface **lst_surf);
void					sprites_shutdown(t_scene *scene);

void					items_init(t_scene *scene, t_map *map);
void					items_update(t_scene *sc, t_state *state, t_ray ray,
							t_surface **lst_surf);
void					items_shutdown(t_scene *scene);

t_surface				*init_door_surface(t_surface *surf, t_pos pos,
							double special);
void					submit_door_surface(t_surface *surf, t_ray ray,
							t_scene *sc, t_surface **lst_surf);
void					doors_init(t_scene *scene, t_map *map);
void					doors_update(t_scene *sc, t_ray ray,
							t_surface **lst_surf);
void					door_standard_update(t_door *door, t_ray ray,
							t_scene *scene, t_surface **lst_surf);
void					door_grid_update(t_door *door, t_ray ray,
							t_scene *scene, t_surface **lst_surf);
void					doors_shutdown(t_scene *scene);

int						sign(double n);
float					born(float val, float min, float max);
double					dist_2d(t_vec a, t_vec b);
t_angle					point_to(t_pos from, t_pos to);
void					direction_from_state(t_vec *vec,
							t_angle yaw, t_angle pitch);
void					direction_rotaxis_from_state(t_vec *vec, t_vec *rotaxis,
							t_angle yaw, t_angle pitch);
void					optimized_rotate_vec(t_vec vec, t_angle phy, t_vec axis,
							t_vec *out);
double					dot_product(t_vec a, t_vec b);
t_vec					cross_product(t_vec a, t_vec b);
t_vec					vec_diff(t_vec a, t_vec b);

void					raytr_init(t_scene *sc);
void					raytr_render(t_scene *sc, t_surface **surfs,
							t_ray ray, t_state *state);
void					add_render_surface(const t_surface *src,
							t_surface **lst, t_scene *scene);
void					update_surface(t_surface *surf);
void					surfaces_pre_tr(t_surface *surfs, t_pos origin);
void					ceilfloor_pre_tr(t_scene *sc, t_pos origin);
void					surfaces_sort(t_surface **surfs);
void					tr_floor(t_ray ray, int *color, const t_scene *sc);
void					tr_ceil(t_ray ray, int *color, const t_scene *sc);
int						tr_correctify_color(int *color, double i_r,
							const t_scene *sc);
void					raytr_shutdown(t_scene *sc);

void					graphical_run(t_scene *scene);
void					graphical_shutdown(t_scene *scene);
void					ctrl_init(t_scene *sc);
void					ctrl_update(t_scene *scene, t_state *state);
void					ctrl_shutdown(t_scene *scene);
int						ctrl_keypress(t_syskey keycode, t_state *state);
int						ctrl_keyrelease(t_syskey keycode, t_state *state);
void					ctrl_releaseall(t_state *state);
int						ctrl_mousemove(int x, int y, t_scene *sc);
bool					physics_can_move(double x, double y,
							const t_scene *scene);
double					physics_get_closest_move(double axis);
void					physics_apply(t_scene *scene);
void					move_forward(t_state *state, int direction);
void					move_side(t_state *state, int direction);
void					jump(t_state *state);
void					move_update(t_state *state);

void					screen_init(t_scene *sc);
void					screen_shutdown(t_scene *sc);
void					textures_load(t_scene *scene);
void					textures_unload(t_scene *scene);
size_t					get_texture_color_at(double x, double y,
							const t_texture *tex, const t_surface *surf);
int						to_x_color(t_color *color);
void					color_darken(int *color, double dark_ratio);
int						fade_color(int c1, int c2, double balance);
bool					write_image(char *file, int *colors,
							size_t width, size_t height);

#endif
