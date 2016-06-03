/*
** shell_background.c for background in /src/shell/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Fri Jun  3 18:08:34 2016 Frederic ODDOU
** Last update Fri Jun  3 18:16:37 2016 Frederic ODDOU
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"

void			shell_background(t_shell	*shell)
{
  t_jobs		*jobs;
  int			status;

  jobs = shell->jobs;
  while (jobs != NULL)
    {
      status = 0;
      if (waitpid(jobs->pid, &status, WNOHANG))
	{
	  printf("[%d]\t+ Done\t%s\n", jobs->id, jobs->name);
          shell->last_return = shell_wait_status(status);
	  utils_jobs_delete_elem(shell, jobs);
	}
      jobs = jobs->next;
    }
}
