/*
** shell_pipe.c for shell in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri May  6 12:29:25 2016 Frederic ODDOU
** Last update Thu May 12 23:31:08 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

void			shell_pipe_close(t_pipe			*pipe)
{
  if (pipe->prev != NULL)
    {
      close(pipe->prev->fd[FD_OUT]);
      close(pipe->fd[FD_IN]);
    }
}

void			shell_pipe_open(t_pipe			*mypipe)
{
  int			fd[2];

  if (mypipe->next)
    {
      pipe(fd);
      mypipe->next->fd[FD_IN] = fd[0];
      mypipe->fd[FD_OUT] = fd[1];
    }
}
