/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Sun May 08 23:59:26 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include "my.h"
#include "shell.h"
#include "builtin.h"
#include "utils.h"
#include "sig_mess.h"
#include "parser.h"

void			shell_treat_pipe_commands(t_shell	*shell,
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
      printf("%s: Command not found.\n", pipe->av[0]);
    }
  shell_close(shell, shell->last_return);
}

static void	shell_treat_pipe_redirection(t_shell 		*shell,
					     t_pipe 		*pipe,
					     int		*fd)
{
  int		flags;

  if (pipe->redi[RED_RIGHT])
    {
      flags = O_RDONLY | O_CREAT | O_RDWR | O_TRUNC;
      fd[FD_OUT] = open(pipe->redi[RED_RIGHT], flags, 0644);
    }
  if (pipe->redi[RED_TWO_RIGHT])
    {
      flags = O_RDONLY | O_CREAT | O_RDWR | O_APPEND;
      fd[FD_OUT] = open(pipe->redi[RED_TWO_RIGHT], flags, 0644);
    }
  if (pipe->redi[RED_LEFT])
    {
      flags = O_RDONLY;
      fd[FD_IN] = open(pipe->redi[RED_LEFT], flags);
    }
  /*
  if (pipe->redi[RED_TWO_LEFT])
    fd[FD_IN] = shell_exe_fils_double_redi(shell, pipe);
  */
  (void)shell;
}

void			shell_treat_pipe_dup(t_shell		*shell,
					     t_list		*list,
					     t_pipe		*pipe)
{
  int		fd[2];

  fd[FD_IN] = 0;
  fd[FD_OUT] = 0;
  shell_treat_pipe_redirection(shell, pipe, fd);
  if (fd[FD_IN])
    {
      if (pipe->fd[FD_IN] != -1)
	close(pipe->fd[FD_IN]);
      pipe->fd[FD_IN] = fd[FD_IN];
    }
  if (fd[FD_OUT])
    {
      if (pipe->fd[FD_OUT] != -1)
	close(pipe->fd[FD_OUT]);
      pipe->fd[FD_OUT] = fd[FD_OUT];
    }
  if (pipe->fd[FD_IN] != -1)
    dup2(pipe->fd[FD_IN], 0);
  if (pipe->fd[FD_OUT] != -1)
    dup2(pipe->fd[FD_OUT], 1);
  shell_pipe_close_next(list->pipe);
}

void			shell_treat_pipe_exec(t_shell		*shell,
					      t_list		*list,
					      t_pipe		*pipe)
{
  if (utils_commands_to_tab(pipe) == true)
    {
      if ((pipe->pid = fork()) == -1)
	{
	  printf("fork function failled.\n");
	  shell_close(shell, EXIT_FAILURE);
	}
      else if (pipe->pid == 0)
	{
	  shell_treat_pipe_dup(shell, list, pipe);
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

bool			shell_get_commands(t_shell		*shell)
{
  char			*str;

  shell_prompt(shell);
  while ((str = get_next_line(STDIN_FILENO)) != NULL)
    {
      parser_control(shell, str);
      free(str);
      shell_list_treat(shell);
      shell_commands_free(shell);
      shell_prompt(shell);
    }
  return (true);
}
