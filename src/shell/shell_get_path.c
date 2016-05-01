/*
** shell_get_path.c for get path in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 12:43:01 2016 Frederic ODDOU
** Last update Sat Apr 30 12:51:19 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

static bool		shell_find_program(t_shell	*shell,
					   t_pipe	*pipe)
{
  int			i;
  int			len;

  i = 0;
  len = strlen(pipe->av[0]);
  if ((pipe->path = malloc(sizeof(char) * (len + 2))) == NULL)
    return (false);
  while (shell->path[i] != NULL)
    {
      len = strlen(pipe->av[0]) + strlen(shell->path[i]) + 2;
      if ((pipe->path = realloc(pipe->path, sizeof(char) * len)) == NULL)
	return (false);
      if (memset(pipe->path, '\0', len) == NULL)
	return (false);
      if ((pipe->path = strcat(pipe->path, shell->path[i])) == NULL ||
	  (pipe->path = strcat(pipe->path, "/")) == NULL ||
	  (pipe->path = strcat(pipe->path, pipe->av[0])) == NULL)
	return (false);
      if (access(pipe->path, X_OK) == 0)
	return (true);
      i++;
    }
  return (false);
}

bool			shell_get_path(t_shell		*shell,
				       t_pipe		*pipe)
{

  if (strncmp(pipe->av[0], "./", 2) && strncmp(pipe->av[0], "/", 1))
    {
      if (shell_find_program(shell, pipe) == true)
	return (true);
    }
  else
    {
      if ((pipe->path = strdup(pipe->av[0])) != NULL)
	{
	  if (access(pipe->path, X_OK) == 0)
	    return (true);
	}
    }
  return (false);
}
