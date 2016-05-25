/*
** parser_control.c for control in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Apr 27 21:53:36 2016 Frederic ODDOU
** Last update Mon May 23 14:36:27 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

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
      shell->commands = utils_commands_go_back(shell->commands);
      utils_commands_delete_list(shell->commands);
      shell->commands = NULL;
      return (false);
    }
  parser_list(shell);
  if (parser_pipe(shell) == false)
    return (false);
  return (true);
}
