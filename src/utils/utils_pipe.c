/*
** utils_pipe.c for utils pipe in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 16:39:30 2016 Frederic ODDOU
** Last update Sat Apr 30 11:47:28 2016 oddou_f
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
      if (tmp->av != NULL)
	free(tmp->av);
      if (tmp->path != NULL)
	free(tmp->path);
      if (tmp->commands != NULL)
	utils_commands_delete_list(tmp->commands);
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
  if (pipe->av != NULL)
    free(pipe->av);
  if (pipe->path != NULL)
    free(pipe->path);
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
  new->av = NULL;
  new->ac = 0;
  new->path = NULL;
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
