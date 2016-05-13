/*
** shell_dup.c for dup in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 10:24:30 2016 Frederic ODDOU
** Last update Fri May 13 19:27:56 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

static void		shell_dup_redirection(t_shell		*shell,
					      t_pipe		*pipe)
{
  int		fd[2];

  fd[FD_IN] = 0;
  fd[FD_OUT] = 0;
  shell_redirection(shell, pipe, fd);
  if (fd[FD_IN] > 0)
    {
      if (pipe->fd[FD_IN] != -1)
	close(pipe->fd[FD_IN]);
      pipe->fd[FD_IN] = fd[FD_IN];
    }
  if (fd[FD_OUT] > 0)
    {
      if (pipe->fd[FD_OUT] != -1)
	close(pipe->fd[FD_OUT]);
      pipe->fd[FD_OUT] = fd[FD_OUT];
    }
}

void			shell_dup(t_shell			*shell,
				  t_pipe			*pipe)
{
  shell_dup_redirection(shell, pipe);
  if ((pipe->fd[FD_IN] != -1 && dup2(pipe->fd[FD_IN], 0) == -1) ||
      (shell->fd[FD_IN] != STDIN_FILENO && dup2(shell->fd[FD_IN], 0) == -1))
    {
      fprintf(stderr, ERROR_FUNCTION, "dup2");
      shell_close(shell, EXIT_FAILURE);
    }
  if ((pipe->fd[FD_OUT] != -1 && dup2(pipe->fd[FD_OUT], 1) == -1) ||
      (shell->fd[FD_OUT] != STDOUT_FILENO && dup2(shell->fd[FD_OUT], 1) == -1))
    {
      fprintf(stderr, ERROR_FUNCTION, "dup2");
      shell_close(shell, EXIT_FAILURE);
    }
  shell_pipe_close(pipe);
  if (pipe->next != NULL)
    close(pipe->next->fd[FD_IN]);
}