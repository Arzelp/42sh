/*
** b_exec.c for exec builtin in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  1 18:55:17 2016 Frederic ODDOU
** Last update Thu May 05 13:44:19 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "builtin.h"

int			b_exec(t_shell			*shell,
			       t_pipe			*pipe)
{
  short			id;

  if ((id = b_is_builtin(pipe->av[0])) != NOT_BUILTIN)
    {
      if (g_builtin[id].func != NULL)
	return ((g_builtin[id].func)(pipe->ac, pipe->av, shell));
    }
  return (1);
}
