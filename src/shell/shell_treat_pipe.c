/*
** shell_treat_pipe.c for treat pipe in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 10:18:46 2016 Frederic ODDOU
** Last update Sun May 22 15:49:25 2016 oddou_f
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
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
    {
      execve(pipe->path, pipe->av, shell->ae);
      if (errno == ENOEXEC)
	{
	  fprintf(stdout,
		  "%s: Exec format error. Binary file not executable.\n",
		  pipe->av[0]);
  	  fprintf(stdout, "Binary file not executable.\n");
	}
      else
	fprintf(stdout, "%s: Permission denied.\n", pipe->av[0]);
      shell->last_return = EXIT_FAILURE;
    }
  else
    {
      shell->last_return = EXIT_FAILURE;
      fprintf(stderr, ERROR_NOTFOUND, pipe->av[0]);
    }
  shell_close(shell, shell->last_return);
}

static void		shell_wait_pipe(t_shell			*shell,
					t_pipe			*pipe)
{
  int			status;

  status = 0;
  if (pipe->prev == NULL)
    {
      waitpid(pipe->pid, &status, WUNTRACED);
      shell_change_tgrp(shell->pid.pgid);
      shell_pipe_close(pipe);
      if (WIFSTOPPED(status))
	{
	  shell->jobs = utils_jobs_add_right(shell->jobs,
					     strdup(pipe->av[0]),
					     pipe->pid);
	  printf("\r[%u]\t+ %d Suspended\t%s\n", shell->jobs->id,
		 shell->jobs->pid, shell->jobs->name);
	  shell->jobs = utils_jobs_go_back(shell->jobs);
	  /*
	  sleep(2);
	  shell_change_tgrp(getpgid(pipe->pid));
	  kill(pipe->pid, SIGCONT);
	  waitpid(pipe->pid, &status, WUNTRACED);
	  */
	}
    }
  else
    waitpid(pipe->pid, &status, WUNTRACED);
  shell->last_return = shell_wait_status(status);
}

static void		shell_treat_pipe_exec_fils(t_shell	*shell,
						   t_pipe	*pipe)
{
  if (pipe->prev == NULL || getpgid(getpid()) == getpgid(getppid()))
    {
      setpgrp();
      shell_change_tgrp(getpgid(getpid()));
    }
  if (shell_dup(shell, pipe) == false)
    shell_close(shell, EXIT_FAILURE);
  if (pipe->next)
    close(pipe->next->fd[FD_IN]);
  shell_treat_pipe_commands(shell, pipe);
}

void			shell_treat_pipe_exec(t_shell		*shell,
					      t_pipe		*pipe)
{
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
	shell_treat_pipe_exec_fils(shell, pipe);
      else if (strcmp(pipe->av[0], "fg") &&
	       b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
	shell->last_return = b_exec(shell, pipe);
    }
  else
    shell->last_return = EXIT_FAILURE;
  shell_pipe_close(pipe);
  shell_end_pipe(shell, pipe);
  if (pipe->commands->index_delim != ID_PARENTHESE &&
      pipe->av != NULL &&
      b_is_builtin(pipe->av[0]) != NOT_BUILTIN &&
      !strcmp(pipe->av[0], "fg"))
    shell->last_return = b_exec(shell, pipe);
}

void			shell_end_pipe(t_shell			*shell,
				       t_pipe			*pipe)
{
  pid_t			pid;
  int			status;

  status = 0;
  if (pipe->next != NULL)
    {
      if ((pid = fork()) == -1)
	{
	  fprintf(stderr, ERROR_FUNCTION, "fork");
	  shell_close(shell, EXIT_FAILURE);
	}
      else if (pid == 0)
	{
	  if (pipe->prev == NULL || getpgid(getpid()) == getpgid(getppid()))
	    setpgid(getpid(), getpgid(pipe->pid));
	  shell_treat_pipe_exec(shell, pipe->next);
	  shell_close(shell, shell->last_return);
	}
      if (pipe->next)
	close(pipe->next->fd[FD_IN]);
      waitpid(pid, &status, WUNTRACED);
      shell->last_return = shell_wait_status(status);
    }
  if (pipe->pid != 0)
    shell_wait_pipe(shell, pipe);
}
