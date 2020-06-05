CC=gcc
#CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g3 -O2 -finline-functions -Ilibft
CFLAGS=-Wall -Wextra -Werror -O2 -finline-functions -Ilibft
NAME=cub3d
DEPS=libft/libft.a -lmlx -lXext -lX11 -lbsd -lm
HEADERS=cub3d.h gnl/get_next_line_bonus.h
SRC=cub3d.c cub3d_file.c cub3d_scene.c cub3d_scene_utils.c cub3d_map.c \
	cub3d_error.c gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c \
	cub3d_map_utils.c cub3d_scene_parsing.c utils.c cub3d_graphics.c \
	cub3d_textures.c cub3d_map_physics.c cub3d_raytr_init.c \
	cub3d_raytr_shutdown.c cub3d_raytr_render.c cub3d_raytr_surfaces.c \
	cub3d_surfaces_utils.c cub3d_2d.c cub3d_3d.c cub3d_controls.c \
	cub3d_color.c cub3d_image.c
OBJ=$(SRC:.c=.o)
SRC_BONUS=
OBJ_BONUS=$(SRC_BONUS:.c=.o)

all: $(NAME) 

$(NAME): $(DEPS) $(OBJ) $(HEADERS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) ${DEPS}

libft/libft.a:
	make -C libft bonus

bonus: $(DEPS) $(OBJ) $(OBJ_BONUS) $(HEADERS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean:	clean	
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
