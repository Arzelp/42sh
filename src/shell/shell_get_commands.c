/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Mon May 09 23:51:36 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my.h"
#include "shell.h"
#include "parser.h"

void			shell_step(t_shell			*shell,
				   char				*str)
{
  shell_commands_free(shell);
  parser_control(shell, str);
  shell_list_treat(shell);
  shell_commands_free(shell);
}

bool			shell_get_commands(t_shell		*shell)
{
  char			*str;

  shell_prompt(shell);
  while ((str = get_next_line(STDIN_FILENO)) != NULL)
    {
      shell_step(shell, str);
      free(str);
      shell_prompt(shell);
    }
  return (true);
}
