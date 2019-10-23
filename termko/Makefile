# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 15:43:45 by ydavis            #+#    #+#              #
#    Updated: 2019/04/18 15:02:41 by ydavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I /usr/local/include libft/libft.a -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
SRC = additional.c color.c color_input.c drawing.c get_lines.c get_mlx.c\
	  helpful.c isometric.c lines_draw.c main.c mlx_helper.c mlx_hooks.c\
	  mouse.c normalize.c perspective.c points.c change_matrix.c\
	  create_matrix.c
OBJ = additional.o color.o color_input.o drawing.o get_lines.o get_mlx.o\
	  helpful.o isometric.o lines_draw.o main.o mlx_helper.o mlx_hooks.o\
	  mouse.o normalize.o perspective.o points.o change_matrix.o\
	  create_matrix.o
HDR = main.h
NAME = fdf
LIBMAKE = libft

all:		$(NAME)

$(NAME):	$(LIBMAKE) $(SRC) $(HDR)
	@make --directory=$(LIBMAKE)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@make --directory=$(LIBMAKE) clean

fclean: clean
	@rm -rf $(NAME)
	@make --directory=$(LIBMAKE) fclean

re:		fclean all
