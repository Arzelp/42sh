##
## Makefile for make in /lib/
##
## Made by Frederic ODDOU
## Login oddou_f <frederic.oddou@epitech.eu>
##
## Started on  Sat Apr 16 11:22:30 2016 Frederic ODDOU
## Last update Sat Apr 16 11:22:30 2016 Frederic ODDOU
##

ECHO		=	/bin/echo -e
DEFAULT	=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED			=	"\033[0;31m"
BLUE		=	"\033[0;34m"

DIRINC	= ../include/

SRC			=  get_next_line.c \
	my_tab_cpy.c \
	my_tab_len.c \
	my_tab_realloc.c \
	my_tab_delete_elem.c \
	my_tab_free.c

CC			= gcc

RM			= rm -f

LIB			=

FLAG		=	-Wall \
	-Wextra \
	-Werror \
	-I ../include/

NAME	= libmy.a

OBJS	= $(SRC:.c=.o)

all:	message $(NAME)

message:
	@$(ECHO) $(BLUE) "  _      _____ ____  " $(DEFAULT)
	@$(ECHO) $(BLUE) " | |    |_   _|  _ \\ " $(DEFAULT)
	@$(ECHO) $(BLUE) " | |      | | | |_) |" $(DEFAULT)
	@$(ECHO) $(BLUE) " | |      | | |  _ <" $(DEFAULT)
	@$(ECHO) $(BLUE) " | |____ _| |_| |_) |" $(DEFAULT)
	@$(ECHO) $(BLUE) " |______|_____|____/" $(DEFAULT)

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS) && \
	 $(ECHO) $(GREEN) "[AR]" $(TEAL) $(NAME) $(DEFAULT) || \
	 $(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re: fclean all

.c.o:
	@gcc $(LIB) $(FLAG) -c $< -o $@ && \
	 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
	 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY: all clean fclean re $(NAME) message
