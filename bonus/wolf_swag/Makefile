##
## Makefile for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
## 
## Made by Tetra
## Login   <arthur.josso@epitech.eu>
## 
## Started on  Thu Dec  3 18:17:06 2015 Tetra
## Last update Tue May 31 10:47:00 2016 Arthur Josso
##

NAME    = 	wolfcurses

CC	= 	gcc

INC     =       ./include/

CFLAGS 	+=	-I/home/${USER}/.froot/include/ \
		-I$(INC) \
		-W -Wall -Wextra

LDFLAGS	+=	-L/home/${USER}/.froot/lib/ \
                -llapin -lsfml-audio -lsfml-graphics -lsfml-window \
                -lsfml-system -lstdc++ -ldl -lm -lncurses

SRC	= 	src/main.c \
		src/wolf.c \
		src/dflt_map.c \
		src/move.c \
		src/lib.c \
		src/get_data.c \
		src/wall_color.c \
		src/get_var.c \
		src/err.c \
		src/load_bmp.c \
		src/getpixel.c \
		src/sprite.c \
		src/loop.c \
		tcore/tekpixel.c \
		tcore/vecnorm.c \
		tcore/go.c \
		tcore/getpixel.c

OBJ	= 	$(SRC:.c=.o)

RM	= 	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) 

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all
