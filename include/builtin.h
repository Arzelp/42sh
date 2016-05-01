/*
** builtin.h for builtin in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 29 23:44:07 2016 Frederic ODDOU
** Last update Sun May 01 18:56:32 2016 oddou_f
*/

#ifndef BUILTIN_
# define BUILTIN_

# include "shell.h"

# define NOT_BUILTIN	-1

typedef struct		s_builtin
{
  char			*name;
  int			(*func)(int ac, char **av, t_shell *shell);
}			t_builtin;

char			*b_getenv(char			**tab,
				  char			*name);

int			b_is_builtin(char		*name);
bool			b_exec(t_shell			*shell,
			       t_pipe			*pipe);

extern t_builtin	g_builtin[];

#endif
