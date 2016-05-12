/*
** shell_treat_backquotes.c for backquote in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 11 19:27:03 2016 Frederic ODDOU
** Last update Thu May 12 21:47:39 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "my.h"
#include "shell.h"
#include "utils.h"

static t_commands	*shell_fork_pere(t_shell		*shell,
					 t_pipe			*mypipe,
					 t_commands		*commands,
					 int			*fd)
{
  char			*str;
  int			status;

  waitpid(mypipe->pid, &status, WUNTRACED);
  shell->last_return = shell_wait_status(status);
  close(fd[1]);
  while ((str = get_next_line(fd[0])) != NULL)
    commands = utils_commands_add_right(commands, str, ID_WITHOUT);
  close(fd[0]);
  return (commands);
}

static t_commands	*shell_fork_backquotes(t_shell		*shell,
					       t_pipe		*mypipe,
					       t_commands	*commands)
{
  int			fd[2];

  if ((pipe(fd)) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "pipe");
      shell_close(shell, EXIT_FAILURE);
    }
  if ((mypipe->pid = fork()) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "fork");
      shell_close(shell, EXIT_FAILURE);
    }
  else if (mypipe->pid == 0)
    {
      close(fd[0]);
      shell->fd[FD_OUT] = fd[1];
      shell_step(shell, strdup(commands->str));
      shell_close(shell, shell->last_return);
    }
  return (shell_fork_pere(shell, mypipe, commands, fd));
}

void			shell_treat_backquotes(t_shell		*shell,
					       t_pipe		*pipe)
{
  t_commands		*commands;
  t_commands		*tmp;

  commands = pipe->commands;
  while (commands != NULL)
    {
      if (commands->index_delim == ID_BACK_QUOTE)
	{
	  tmp = commands;
	  commands = shell_fork_backquotes(shell, pipe, commands);
	  utils_pipe_delete_command(pipe, tmp);
	}
      if (commands != NULL)
	commands = commands->next;
    }
}
