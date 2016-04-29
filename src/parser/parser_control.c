/*
** parser_control.c for control in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Apr 27 21:53:36 2016 Frederic ODDOU
** Last update Fri Apr 29 16:30:14 2016 oddou_f
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

void			display_commands(t_commands		*tmp)
{
  while (tmp != NULL)
    {
      printf("%s ", tmp->str ? tmp->str : "");
      tmp = tmp->next;
    }
}

void			display_pipe(t_pipe			*pipe)
{
  while (pipe != NULL)
    {
      display_commands(pipe->commands);
      if (pipe->next != NULL)
	printf("| ");
      pipe = pipe->next;
    }
}

void			display_list(t_shell			*shell)
{
  t_list		*tmp;

  tmp = shell->list;
  while (tmp != NULL)
    {
      display_pipe(tmp->pipe);
      printf("\n");
      tmp = tmp->next;
    }
}

/*
** Controle du parser :
** 1- On sépares toutes les chaines de caractères
** 2- On fait un controle des séparateurs
** 3- On sépare toutes les listes de commandes (&& || ;)
** 4- On sépare dans les listes toutes les pipes
*/
bool			parser_control(t_shell			*shell,
				       char			*str)
{
  if (parser_commands(shell, str) == false ||
      parser_check_separator(shell) == false)
    {
      utils_commands_delete_list(shell->commands);
      shell->commands = NULL;
      return (false);
    }
  parser_list(shell);
  if (parser_pipe(shell) == false)
    return (false);
  display_list(shell);
  return (true);
}
