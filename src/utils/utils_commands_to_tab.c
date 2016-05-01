/*
** utils_commands_to_tab.c for commands to tab in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 10:43:24 2016 Frederic ODDOU
** Last update Sat Apr 30 11:08:31 2016 oddou_f
*/

#include <stdlib.h>
#include <stdbool.h>
#include "shell.h"

static unsigned int	utils_commands_count(t_commands		*commands)
{
  unsigned int		nb;

  nb = 0;
  while (commands != NULL)
    {
      nb++;
      commands = commands->next;
    }
  return (nb);
}

bool			utils_commands_to_tab(t_pipe		*pipe)
{
  int			i;
  t_commands		*tmp;

  if (pipe == NULL)
    return (false);
    tmp = pipe->commands;
  if ((pipe->ac = utils_commands_count(tmp)) <= 0)
    return (false);
  if ((pipe->av = malloc(sizeof(char *) * (pipe->ac + 1))) == NULL)
    return (false);
  i = 0;
  while (i < pipe->ac)
    {
      pipe->av[i] = tmp->str;
      tmp = tmp->next;
      i++;
    }
  pipe->av[i] = NULL;
  return (true);
}
