/*
** shell_list.c for shell list in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  8 15:17:14 2016 Frederic ODDOU
** Last update Sun May 22 14:24:43 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"

static void		shell_list_desactive(t_list	*list,
					     short	id_sep)
{
  while (list != NULL && list->type_separator == id_sep)
    {
      list->treat = false;
      list = list->next;
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

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



void			shell_exec_pipe(t_shell		*shell,
					t_pipe		*pipe,
					t_list		*list)
{
  pid_t		pid;
  int		status;

  //printf("pere : %d / pid : %d / groupe : %d\n", getppid(), getpid(), getpgid(getpid()));
  shell_pipe_open(pipe);
  if (pipe->commands->index_delim == ID_PARENTHESE)
    shell->last_return = shell_treat_parenthese(shell, pipe);
  else if (utils_commands_to_tab(shell, pipe) == true)
    {
      if ((pipe->pid = fork()) == -1)
	{
	  fprintf(stderr, ERROR_FUNCTION, "fork");
	  shell_close(shell, EXIT_FAILURE);
	}
      else if (pipe->pid == 0)
	{
	  shell_dup(shell, pipe);
	  if (pipe->next)
	    close(pipe->next->fd[FD_IN]);
	  shell_treat_pipe_commands(shell, pipe);
	}
      else if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
	shell->last_return = b_exec(shell, pipe);
    }
  shell_pipe_close(pipe);
  if (pipe->next != NULL)
    {
      if ((pid = fork()) == -1)
      	{
      	  fprintf(stderr, ERROR_FUNCTION, "fork");
      	  shell_close(shell, EXIT_FAILURE);
	}
      else if (pid == 0)
	{
	  shell_exec_pipe(shell, pipe->next, list);
      	  shell_close(shell, shell->last_return);
        }
      if (pipe->next)
	close(pipe->next->fd[FD_IN]);
      waitpid(pid, &status, WUNTRACED);
      shell->last_return = shell_wait_status(status);
    }
  if (pipe->pid != 0)
    {
      waitpid(pipe->pid, &status, WUNTRACED);
      shell_pipe_close(pipe);
      shell->last_return = shell_wait_status(status);
    }
}




bool			shell_list_treat(t_shell	*shell)
{
  t_list		*list;

  list = shell->list;
  while (list != NULL)
    {
      if (list->treat == true)
	{
	  shell_exec_pipe(shell, list->pipe, list);
	  //shell_treat_pipe_wait(shell, list->pipe);
	  if (shell->last_return != EXIT_SUCCESS)
	    shell_list_desactive(list->next, ID_AND);
	  else
	    shell_list_desactive(list->next, ID_OR);
	}
      list = list->next;
    }
  return (true);
}
