/*
** shell_exec.c for shell exec in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  1 18:41:58 2016 Frederic ODDOU
** Last update Sun May 08 18:13:12 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include "shell.h"
#include "sig_mess.h"

static void		shell_exec_fils(t_shell		*shell,
					t_pipe		*pipe)
{
  shell_signal(false);
  execve(pipe->path, pipe->av, shell->ae);
  shell_close(shell, EXIT_FAILURE);
}

static void		shell_exec_pere(t_shell		*shell,
					pid_t		pid)
{
  int			status;

  waitpid(pid, &status, WUNTRACED);
  if (WIFSIGNALED(status))
    {
      sig_display(status);
      shell->last_return = (SCHAR_MAX + 1) + WTERMSIG(status);
    }
  else if (WIFEXITED(status))
    shell->last_return = WEXITSTATUS(status);
  else if (WIFSTOPPED(status))
    {
      shell->last_return = WSTOPSIG(status);
      printf("Suspended\n");
    }
}

bool			shell_exec(t_shell		*shell,
				   t_pipe		*pipe)
{
  pid_t			pid;

  if ((pid = fork()) == -1)
    {
      printf("fork function failled.\n");
      shell_close(shell, EXIT_FAILURE);
    }
  else if (pid == 0)
    shell_exec_fils(shell, pipe);
  else
    shell_exec_pere(shell, pid);
  return ((shell->last_return != EXIT_SUCCESS) ? false : true);
}
