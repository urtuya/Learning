SRC = main.c init.c draw.c iso.c hooks.c rotation.c perspective.c
TOOL = -I /usr/local/include/ -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all:
	gcc -g $(SRC) $(TOOL) libft/libft.a

clean:
	make clean -C libft
	rm *.o
