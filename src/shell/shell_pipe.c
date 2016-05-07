/*
** shell_pipe.c for shell in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri May  6 12:29:25 2016 Frederic ODDOU
** Last update Sat May 07 22:16:32 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

static int	shell_pipe_count(t_pipe		*mypipe)
{
  int		count;

  count = 0;
  while (mypipe != NULL)
    {
      count++;
      mypipe = mypipe->next;
    }
  return (count);
}

void		shell_pipe_close(t_shell	*shell,
				 t_pipe		*mypipe)
{
  int		count;
  int		i;

  i = 0;
  count = shell_pipe_count(mypipe);
  while (i < (count - 1) * 2)
    {
      close(shell->list_fd[i]);
      i++;
    }
  free(shell->list_fd);
  shell->list_fd = NULL;
}

int		*shell_pipe_open(t_shell	*shell,
				 t_pipe		*mypipe)
{
  int		fd[2];
  int		*list_fd;
  int		count;
  int		i;

  if ((count = shell_pipe_count(mypipe)) == 0 ||
      (list_fd = malloc(sizeof(int) * ((count - 1) * 2))) == NULL)
    return (NULL);
  i = 0;
  while (mypipe != NULL && mypipe->next != NULL)
    {
      if ((pipe(fd)) == -1)
	{
	  free(list_fd);
	  fprintf(stderr, "Error : fork function failled.\n");
	  shell_close(shell, EXIT_FAILURE);
	}
      mypipe->next->fd[FD_IN] = fd[0];
      mypipe->fd[FD_OUT] = fd[1];
      list_fd[i] = fd[0];
      list_fd[i + 1] = fd[1];
      i += 2;
      mypipe = mypipe->next;
    }
  return (list_fd);
}
