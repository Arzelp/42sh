/*
** shell_list.c for shell list in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  8 15:17:14 2016 Frederic ODDOU
** Last update Mon May 09 10:35:35 2016 oddou_f
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

bool			shell_list_treat(t_shell	*shell)
{
  t_list		*list;

  list = shell->list;
  while (list != NULL)
    {
      if (list->treat == true)
	{
	  shell_pipe_open(shell, list->pipe);
	  shell_treat_pipe_exec(shell, list, list->pipe);
	  shell_treat_pipe_wait(shell, list->pipe);
	  if (shell->last_return != EXIT_SUCCESS)
	    shell_list_desactive(list->next, ID_AND);
	  else
	    shell_list_desactive(list->next, ID_OR);
	}
      list = list->next;
    }
  return (true);
}
