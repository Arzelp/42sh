/*
** shell.h for shell in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:39 2016 Frederic ODDOU
** Last update Sun May 01 18:42:22 2016 oddou_f
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <stdbool.h>
# include "enum.h"

typedef struct		s_commands
{
  char			*str;
  short			index_delim;
  struct s_commands	*next;
  struct s_commands	*prev;
}			t_commands;

typedef struct		s_pipe
{
  t_commands		*commands;
  int			ac;
  char			**av;
  char			*path;
  struct s_pipe		*next;
  struct s_pipe		*prev;
}			t_pipe;

typedef struct		s_list
{
  t_commands		*commands;
  t_pipe		*pipe;
  short			type_separator;
  bool			treat;
  struct s_list		*next;
  struct s_list		*prev;
}			t_list;

typedef struct		s_locales
{
  char			*name;
  char			*value;
  struct s_locales	*next;
  struct s_locales	*prev;
}			t_locales;

typedef struct		s_shell
{
  int			last_return;
  char			**ae;
  t_locales		*locales;
  char			**path;
  t_commands		*commands;
  t_list		*list;
}			t_shell;

bool			shell_init(t_shell			*shell,
				   int				ac,
				   char				**av,
				   char				**ae);
bool			shell_close(t_shell			*shell,
				    unsigned char		value);
bool			shell_get_commands(t_shell		*shell);
void			shell_commands_free(t_shell		*shell);
bool			shell_get_path(t_shell			*shell,
				       t_pipe			*pipe);
bool			shell_exec(t_shell			*shell,
				   t_pipe			*pipe);

#endif
