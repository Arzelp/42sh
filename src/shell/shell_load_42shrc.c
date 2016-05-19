/*
** shell_load_42shrc.c for load in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May 19 13:18:44 2016 Frederic ODDOU
** Last update Thu May 19 13:56:45 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "shell.h"
#include "my.h"

bool			shell_load_42shrc(t_shell		*shell)
{
  int			fd;
  char			*str;
  int			size;
  char			*next;

  size = 0;
  str = NULL;
  if ((next = strdup("")) == NULL)
    return (false);
  if ((fd = open(SHRC, O_RDONLY)) == -1)
    return (false);
  while ((str = get_next_line(fd, &next, &size)) != NULL)
    shell_step(shell, str);
  if (next != NULL)
    free(next);
  close(fd);
  return (true);
}
