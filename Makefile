##
## Makefile for 42 make in /
##
## Made by Frederic ODDOU
## Login oddou_f <frederic.oddou@epitech.eu>
##
## Started on  Sat Apr 16 10:50:08 2016 Frederic ODDOU
## Last update Thu May 19 15:11:58 2016 alies_a
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"
BLUE		=	"\033[0;34m"

DIR_INC = ./include/
DIR_LIB = ./lib/my/
DIR_SRC = ./src/

CH_PATH		=	./lib/getch/
CH_INC		=	./lib/getch/include/

DIR_SHELL	=	$(DIR_SRC)shell/
DIR_PARSER	= 	$(DIR_SRC)parser/
DIR_UTILS	=	$(DIR_SRC)utils/
DIR_BUILTIN	=	$(DIR_SRC)builtin/

SRC 	=	$(DIR_SRC)main.c \
		$(DIR_SHELL)shell_close.c \
		$(DIR_SHELL)shell_init.c \
		$(DIR_SHELL)shell_get_commands.c \
		$(DIR_SHELL)shell_commands_free.c \
		$(DIR_SHELL)shell_get_path.c \
		$(DIR_SHELL)shell_pipe.c \
		$(DIR_SHELL)shell_dup.c \
		$(DIR_SHELL)shell_treat_pipe.c \
		$(DIR_SHELL)shell_treat_parenthese.c \
		$(DIR_SHELL)shell_treat_backquotes.c \
		$(DIR_SHELL)shell_treat_glob.c \
		$(DIR_SHELL)shell_prompt.c \
		$(DIR_SHELL)shell_list.c \
		$(DIR_SHELL)shell_redirection.c \
		$(DIR_SHELL)shell_load_42shrc.c \
		$(DIR_SHELL)shell_signaux.c \
		$(DIR_SHELL)shell_wait_status.c \
		$(DIR_PARSER)parser_commands.c \
		$(DIR_PARSER)parser_commands_backslash.c \
		$(DIR_PARSER)parser_control.c \
		$(DIR_PARSER)parser_list.c \
		$(DIR_PARSER)parser_pipe.c \
		$(DIR_PARSER)parser_redi.c \
		$(DIR_PARSER)parser_check_separator.c \
		$(DIR_UTILS)utils_commands.c \
		$(DIR_UTILS)utils_commands_to_tab.c \
		$(DIR_UTILS)utils_list.c \
		$(DIR_UTILS)utils_pipe.c \
		$(DIR_UTILS)utils_locales.c \
		$(DIR_UTILS)utils_signal.c \
		$(DIR_UTILS)utils_alias.c \
		$(DIR_UTILS)utils_get_var.c \
		$(DIR_UTILS)utils_tab_fusion.c \
		$(DIR_UTILS)utils_get_homepath.c \
		$(DIR_UTILS)utils_alias_replace.c \
		$(DIR_BUILTIN)b_getenv.c \
		$(DIR_BUILTIN)b_exec.c \
		$(DIR_BUILTIN)b_is_builtin.c \
		$(DIR_BUILTIN)b_env.c \
		$(DIR_BUILTIN)b_setenv.c \
		$(DIR_BUILTIN)b_unsetenv.c \
		$(DIR_BUILTIN)b_which.c \
		$(DIR_BUILTIN)b_exit.c \
		$(DIR_BUILTIN)b_cd.c \
		$(DIR_BUILTIN)b_set.c \
		$(DIR_BUILTIN)b_alias.c \
		$(DIR_BUILTIN)b_builtins.c \
		$(DIR_SRC)vars.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wextra \
		-Wall \
		-Werror \
		-I$(DIR_INC) -I$(CH_INC) -g

LDFLAGS	=	-L ./lib/my/ \
		-l my \
		-L $(CH_PATH) \
		-l getch \

NAME	=	42sh

all:		libmy getch message $(NAME)

message:
	@$(ECHO) $(BLUE) "  _  _  ___    _____  _    _ " $(DEFAULT)
	@$(ECHO) $(BLUE) " | || ||__ \  / ____|| |  | |" $(DEFAULT)
	@$(ECHO) $(BLUE) " | || |_  ) || (___  | |__| |" $(DEFAULT)
	@$(ECHO) $(BLUE) " |__   _|/ /  \___ \ |  __  |" $(DEFAULT)
	@$(ECHO) $(BLUE) "    | | / /_  ____) || |  | |" $(DEFAULT)
	@$(ECHO) $(BLUE) "    |_||____||_____/ |_|  |_|" $(DEFAULT)

libmy:
		@make -C $(DIR_LIB) -f Makefile -s

getch:
		@make -C $(CH_PATH) -f Makefile -s

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		@make clean -C $(DIR_LIB) -f Makefile -s
		@make clean -C $(CH_PATH) -f Makefile -s
		@$(RM) $(OBJ)

fclean:		clean
		@make fclean -C $(DIR_LIB) -f Makefile -s
		@make fclean -C $(CH_PATH) -f Makefile -s
		@$(RM) ./$(NAME)

re:		fclean all

.c.o:
		@gcc $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY: all clean fclean re libmy getch $(NAME) .c.o message
