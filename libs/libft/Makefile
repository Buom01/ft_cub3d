# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badam <badam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/22 22:32:31 by badam             #+#    #+#              #
#    Updated: 2020/07/13 00:17:02 by badam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -O3
NAME=libft.a
SRC= $(filter-out %_bonus.%,$(wildcard ft_*.c))
OBJ= $(SRC:.c=.o)
SRC_BONUS= $(filter %_bonus.%,$(wildcard ft_*.c))
OBJ_BONUS= $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

fclean:	clean	
	rm -rf $(NAME)

re: fclean all
