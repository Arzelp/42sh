/*
** shell_get_path.c for get path in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 12:43:01 2016 Frederic ODDOU
** Last update Thu May 05 14:59:17 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

static char		*shell_find_program(t_shell	*shell,
					   char		*name)
{
  int			i;
  int			len;
  char			*str;

  i = 0;
  len = strlen(name);
  if ((str = malloc(sizeof(char) * (len + 2))) == NULL)
    return (NULL);
  while (shell->path[i] != NULL)
    {
      len = strlen(name) + strlen(shell->path[i]) + 2;
      if ((str = realloc(str, sizeof(char) * len)) == NULL)
	return (NULL);
      if (memset(str, '\0', len) == NULL)
	return (NULL);
      if ((str = strcat(str, shell->path[i])) == NULL ||
	  (str = strcat(str, "/")) == NULL ||
	  (str = strcat(str, name)) == NULL)
	return (NULL);
      if (access(str, X_OK) == 0)
	return (str);
      i++;
    }
  free(str);
  return (NULL);
}

char			*shell_get_path(t_shell		*shell,
					char		*name)
{
  char			*str;

  if (name == NULL)
    return (NULL);
  if (strncmp(name, "./", 2) && strncmp(name, "/", 1))
    {
      if ((str = shell_find_program(shell, name)) != NULL)
	return (str);
    }
  else
    {
      if (access(name, X_OK) == 0)
	return (strdup(name));
    }
  return (NULL);
}
