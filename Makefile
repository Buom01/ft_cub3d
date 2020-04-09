CC=gcc
CFLAGS=-Wall -Wextra -Werror -Ilibft
NAME=cub3d
DEPS=libft/libft.a
HEADERS=cub3d.h macro.h gnl/get_next_line_bonus.h
SRC=cub3d.c cub3d_file.c cub3d_scene.c cub3d_error.c \
	gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
OBJ=$(SRC:.c=.o)
SRC_BONUS=
OBJ_BONUS=$(SRC_BONUS:.c=.o)

all: $(NAME) 

$(NAME): $(DEPS) $(OBJ) $(HEADERS)
	$(CC) -o $(NAME) $(OBJ) ${DEPS}

libft/libft.a:
	make -C libft bonus

bonus: $(DEPS) $(OBJ) $(OBJ_BONUS) $(HEADERS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean:	clean	
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
