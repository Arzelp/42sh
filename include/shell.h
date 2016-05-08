/*
** shell.h for shell in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:39 2016 Frederic ODDOU
** Last update Sun May 08 23:31:40 2016 oddou_f
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
  pid_t			pid;
  t_commands		*commands;
  int			ac;
  char			**av;
  char			*path;
  int			fd[2];
  char			*redi[4];
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

typedef struct		s_pid
{
  pid_t			pid;
  pid_t			pgid;
}			t_pid;

typedef struct		s_shell
{
  bool			write;
  int			last_return;
  t_pid			pid;
  char			*oldpwd;
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
void			shell_signal(bool			ign);
bool			shell_close(t_shell			*shell,
				    unsigned char		value);
bool			shell_get_commands(t_shell		*shell);
void			shell_commands_free(t_shell		*shell);
char			*shell_get_path(t_shell			*shell,
					char			*name);
bool			shell_exec(t_shell			*shell,
				   t_pipe			*pipe);


void			shell_list_desactive(t_list		*list,
					     short		id_sep);
bool			shell_list_treat(t_shell		*shell);
void			shell_treat_pipe_exec(t_shell		*shell,
					      t_list		*list,
					      t_pipe		*pipe);
void			shell_treat_pipe_wait(t_shell		*shell,
					      t_pipe		*pipe);
void			shell_prompt(t_shell			*shell);

/*
** shell_pipe.c
*/
void			shell_pipe_close_fd(t_pipe		*pipe);
void			shell_pipe_close_next(t_pipe		*pipe);
void			shell_pipe_open(t_shell			*shell,
					t_pipe			*mypipe);

#endif
