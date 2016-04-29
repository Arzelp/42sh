/*
** utils_pipe.c for utils pipe in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 16:39:30 2016 Frederic ODDOU
** Last update Thu Apr 28 16:50:48 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"

void			utils_pipe_delete_list(t_pipe		*pipe)
{
  t_pipe		*tmp;

  while (pipe != NULL)
    {
      tmp = pipe;
      pipe = pipe->next;
      if (tmp->commands != NULL)
	utils_commands_delete_list(pipe->commands);
      free(tmp);
    }
}

void			utils_pipe_delete_elem(t_list		*list,
					       t_pipe		*pipe)
{
  if (pipe->prev != NULL)
    pipe->prev->next = pipe->next;
  else
    list->pipe = pipe->next;
  if (pipe->next != NULL)
    pipe->next->prev = pipe->prev;
  if (pipe->commands != NULL)
    utils_commands_delete_list(pipe->commands);
  free(pipe);
}

t_pipe			*utils_pipe_add_right(t_pipe		*pipe,
					      t_commands	*commands)
{
  t_pipe		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->prev = pipe;
  new->next = NULL;
  new->commands = commands;
  if (pipe != NULL)
    {
      if (pipe->next != NULL)
	{
	  new->next = pipe->next;
	  pipe->next->prev = new;
	}
      pipe->next = new;
    }
  return (new);
}

t_pipe			*utils_pipe_go_back(t_pipe		*pipe)
{
  while (pipe != NULL && pipe->prev != NULL)
    pipe = pipe->prev;
  return (pipe);
}
