# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badam <badam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/10 18:46:41 by badam             #+#    #+#              #
#    Updated: 2020/07/18 13:35:42 by badam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
#CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g3 -Isrcs -Ilibs/libft
CFLAGS=-Wall -Wextra -Werror -Ofast -flto -Isrcs -Ilibs/libft
NAME=Cub3D
DEPS=libs/libft/libft.a -lmlx -lXext -lX11 -lm
HEADERS= \
	srcs/cub3d.h \
	libs/gnl/get_next_line_bonus.h
SRC= \
	libs/gnl/get_next_line_utils_bonus.c \
	libs/gnl/get_next_line_bonus.c \
	srcs/utils/utils.c \
	srcs/utils/surfaces.c \
	srcs/utils/math.c \
	srcs/utils/math_2d.c \
	srcs/utils/math_3d.c \
	srcs/utils/color.c \
	srcs/utils/file.c \
	srcs/map/utils.c \
	srcs/map/parsing.c \
	srcs/map/map.c \
	srcs/surfaces.c \
	srcs/entities/walls.c \
	srcs/entities/fakewalls.c \
	srcs/entities/items.c \
	srcs/entities/sprites.c \
	srcs/entities/doors/standard.c \
	srcs/entities/doors/doors.c \
	srcs/raytracing/utils.c \
	srcs/raytracing/surfaces.c \
	srcs/raytracing/init.c \
	srcs/raytracing/render_ceilfloor.c \
	srcs/raytracing/render.c \
	srcs/scene/utils.c \
	srcs/scene/parsing.c \
	srcs/scene/parsing_utils.c \
	srcs/scene/scene.c \
	srcs/scene/shutdown.c \
	srcs/mlx/mlx.c \
	srcs/error.c \
	srcs/textures.c \
	srcs/screen.c \
	srcs/graphics.c \
	srcs/images/bmp.c \
	srcs/physics/utils.c \
	srcs/physics/apply.c \
	srcs/physics/physics.c \
	srcs/move.c \
	srcs/controls.c \
	srcs/controls_events.c \
	srcs/cub3d.c
OBJ=$(SRC:.c=.o)
SRC_BONUS=
OBJ_BONUS=$(SRC_BONUS:.c=.o)

all: $(NAME) 

bonus: $(NAME) 

$(NAME): $(DEPS) $(OBJ) $(HEADERS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) ${DEPS}

libs/libft/libft.a:
	make -C libs/libft bonus

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)
	make -C libs/libft clean

fclean:	clean	
	rm -rf $(NAME)
	make -C libs/libft fclean

re: fclean all
