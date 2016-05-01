/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Sun May 01 19:27:26 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "shell.h"
#include "builtin.h"
#include "utils.h"
#include "parser.h"

void			shell_desactive_list(t_list	*list,
					     short	id_sep)
{
  while (list != NULL && list->type_separator == id_sep)
    {
      list->treat = false;
      list = list->next;
    }
}

bool			shell_treat_pipe(t_shell	*shell,
					 t_list		*list)
{
  t_pipe		*pipe;

  pipe = list->pipe;
  while (pipe != NULL)
    {
      if (utils_commands_to_tab(pipe) == true)
	{
	  if (b_is_builtin(pipe->av[0]) != NOT_BUILTIN)
	    b_exec(shell, pipe);
	  else if (shell_get_path(shell, pipe) == true)
	    shell_exec(shell, pipe);
	  else
	    {
	      shell->last_return = EXIT_FAILURE;
	      printf("%s: Command not found.\n", pipe->av[0]);
	    }
	  if (shell->last_return != EXIT_SUCCESS)
	    shell_desactive_list(list->next, ID_AND);
	  else
	    shell_desactive_list(list->next, ID_OR);
	}
      pipe = pipe->next;
    }
  return (true);
}

bool			shell_treat_list(t_shell	*shell)
{
  t_list		*list;

  list = shell->list;
  while (list != NULL)
    {
      if (list->treat == true)
	{
	  if (shell_treat_pipe(shell, list) == false)
	    return (false);
	}
      list = list->next;
    }
  return (true);
}

bool			shell_get_commands(t_shell	*shell)
{
  char			*str;

  printf("?> ");
  fflush(stdout);
  while ((str = get_next_line(STDIN_FILENO)) != NULL)
    {
      parser_control(shell, str);
      free(str);
      shell_treat_list(shell);
      shell_commands_free(shell);
      printf("?> ");
      fflush(stdout);
    }
  return (true);
}
