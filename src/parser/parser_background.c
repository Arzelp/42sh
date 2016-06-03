/*
** parser_background.c for background in /src/parser/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 17:23:05 2016 Frederic ODDOU
** Last update Fri Jun  3 17:38:07 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

static bool		parser_background_find(t_pipe		*pipe,
					       t_list		*list)
{
  t_commands		*commands;

  while (pipe != NULL)
    {
      commands = pipe->commands;
      while (commands != NULL)
	{
	  if (commands->index_delim == ID_BACKGROUND)
	    {
	      if (pipe->next)
		{
		  fprintf(stdout, "%s\n", ERR_NULL);
		  return (false);
		}
	      list->background = true;
	      utils_commands_purge_elem(commands);
	      return (parser_background_find(pipe, list));
	    }
	  commands = commands->next;
	}
      pipe = pipe->next;
    }
  return (true);
}

bool			parser_background(t_shell		*shell)
{
  t_list		*tmp;

  tmp = shell->list;
  while (tmp != NULL)
    {
      if (parser_background_find(tmp->pipe, tmp) == false)
	return (false);
      tmp = tmp->next;
    }
  return (true);
}
