/*
** shell_script.c for shell script in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May 23 15:06:32 2016 Frederic ODDOU
** Last update Mon May 23 15:18:08 2016 oddou_f
*/

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "my.h"

bool			shell_script(t_shell	*shell,
				     char	*file)
{
  int			fd;
  char			*str;
  int			size;
  char			*next;

  if ((fd = open(file, O_RDONLY)) == -1)
    {
      fprintf(stderr, "%s: Aucun fichier ou dossier de ce type.\n", file);
      return (false);
    }
  size = 0;
  str = NULL;
  if ((next = strdup("")) == NULL)
    return (false);
  while ((str = get_next_line(fd, &next, &size)) != NULL)
    {
      if (strlen(str) > 0)
	shell->history = utils_history_add_right(shell->history, strdup(str));
      shell_step(shell, str);
    }
  free(next);
  close(fd);
  return (true);
}
