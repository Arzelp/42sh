/*
** shell_treat_pipe.c for treat pipe in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 10:18:46 2016 Frederic ODDOU
** Last update Mon May 09 10:37:47 2016 oddou_f
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"
#include "sig_mess.h"

static void		shell_treat_pipe_commands(t_shell	*shell,
						  t_pipe	*pipe)
{
  shell->write = true;
  shell->last_return = 0;
  shell_signal(false);
  if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
    shell->last_return = b_exec(shell, pipe);
  else if ((pipe->path = shell_get_path(shell, pipe->av[0])) != NULL)
    execve(pipe->path, pipe->av, shell->ae);
  else
    {
      shell->last_return = EXIT_FAILURE;
      fprintf(stderr, ERROR_NOTFOUND, pipe->av[0]);
    }
  shell_close(shell, shell->last_return);
}

void			shell_treat_pipe_exec(t_shell		*shell,
					      t_list		*list,
					      t_pipe		*pipe)
{
  if (utils_commands_to_tab(pipe) == true)
    {
      if ((pipe->pid = fork()) == -1)
	{
	  fprintf(stderr, ERROR_FUNCTION, "fork");
	  shell_close(shell, EXIT_FAILURE);
	}
      else if (pipe->pid == 0)
	{
	  shell_dup(shell, list, pipe);
	  shell_treat_pipe_commands(shell, pipe);
	}
      else if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
	shell->last_return = b_exec(shell, pipe);
    }
  shell_pipe_close_fd(pipe);
  if (pipe->next)
    shell_treat_pipe_exec(shell, list, pipe->next);
}

void			shell_treat_pipe_wait(t_shell		*shell,
					      t_pipe		*pipe)
{
  int			status;

  shell->last_return = 0;
  while (pipe != NULL)
    {
      waitpid(pipe->pid, &status, WUNTRACED);
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
      pipe = pipe->next;
    }
}
