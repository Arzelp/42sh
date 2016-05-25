/*
** shell_treat_glob.c for glob in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May 12 21:31:22 2016 Frederic ODDOU
** Last update Mon May 16 17:13:13 2016 oddou_f
*/

#include <stdlib.h>
#include <glob.h>
#include <string.h>
#include "my.h"
#include "shell.h"
#include "utils.h"

static bool		shell_if_glob(char			*str)
{
  if (str == NULL)
    return (false);
  while (*str != '\0')
    {
      if (*str == '*')
	return (true);
      str = str + 1;
    }
  return (false);
}

static t_commands	*shell_glob_find(t_commands		*commands)
{
  glob_t		globbuf;
  int			i;

  i = 0;
  if (glob(commands->str, 0, NULL, &globbuf) != 0)
    return (commands);
  if (globbuf.gl_pathv == NULL)
    return (commands);
  while (globbuf.gl_pathv[i] != NULL)
    {
      commands = utils_commands_add_right(commands,
					  strdup(globbuf.gl_pathv[i]),
					  ID_WITHOUT);
      i++;
    }
  globfree(&globbuf);
  return (commands);
}

void			shell_treat_glob(t_pipe			*pipe)
{
  t_commands		*commands;
  t_commands		*tmp;
  t_commands		*tmp_next;

  commands = pipe->commands;
  while (commands != NULL)
    {
      if (commands->index_delim == ID_WITHOUT && shell_if_glob(commands->str))
	{
	  tmp = commands;
	  tmp_next = tmp->next;
	  commands = shell_glob_find(commands);
	  utils_pipe_delete_command(pipe, tmp);
	  commands = tmp_next;
	}
      else
	commands = commands->next;
    }
}
