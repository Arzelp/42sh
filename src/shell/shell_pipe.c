/*
** shell_pipe.c for shell in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri May  6 12:29:25 2016 Frederic ODDOU
** Last update Sun May 08 22:57:05 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

void			shell_pipe_close_fd(t_pipe		*pipe)
{
  if (pipe->fd[FD_IN] != -1)
    close(pipe->fd[FD_IN]);
  if (pipe->fd[FD_OUT] != -1)
    close(pipe->fd[FD_OUT]);
}

void			shell_pipe_close_next(t_pipe		*pipe)
{
  while (pipe != NULL)
    {
      shell_pipe_close_fd(pipe);
      pipe = pipe->next;
    }
}

void			shell_pipe_open(t_shell			*shell,
					t_pipe			*mypipe)
{
  int			fd[2];

  while (mypipe != NULL && mypipe->next != NULL)
    {
      if ((pipe(fd)) == -1)
	{
	  fprintf(stderr, "Error : fork function failled.\n");
	  shell_close(shell, EXIT_FAILURE);
	}
      mypipe->next->fd[FD_IN] = fd[0];
      mypipe->fd[FD_OUT] = fd[1];
      mypipe = mypipe->next;
    }
}
