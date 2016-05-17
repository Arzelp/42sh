/*
** builtin.h for builtin in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:44:07 2016 Frederic ODDOU
** Last update Sat May 14 23:26:52 2016 oddou_f
*/

#pragma once

#include "shell.h"

#define NOT_BUILTIN	-1
#define NOT_ID		-1
#define ERROR_FATAL	-1

#define TOO_ARG		"%s: Too many arguments.\n"
#define FEW_ARG		"%s: Too few arguments.\n"
#define NO_FOLDER	"%s: Aucun fichier ou dossier de ce type.\n"
#define SYNTAX_EXP	"%s: Expression Syntax.\n"
#define IS_BUILTIN	"%s: shell built-in command.\n"

typedef struct		s_builtin
{
  char			*name;
  int			(*func)(int ac, char **av, t_shell *shell);
}			t_builtin;

char			*b_getenv(char			**tab,
				  char			*name);
char			*b_findenv(char			**tab,
				   char			*name);
int			b_get_id_env(char		**tab,
				     char		*name);

short			b_is_builtin(char		*name);
int			b_exec(t_shell			*shell,
			       t_pipe			*pipe);

int			b_env(int			ac,
			      char			**av,
			      t_shell			*shell);
int			b_setenv(int			ac,
				 char			**av,
				 t_shell		*shell);
int			b_unsetenv(int			ac,
				   char			**av,
				   t_shell		*shell);
int			b_which(int			ac,
				char			**av,
				t_shell			*shell);
int			b_exit(int			ac,
			       char			**av,
			       t_shell			*shell);
int			b_cd(int			ac,
			     char			**av,
			     t_shell			*shell);
int			b_builtins(int			ac,
				   char			**av,
				   t_shell		*shell);

extern t_builtin	g_builtin[];
