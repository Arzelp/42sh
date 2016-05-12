/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Fri May 13 00:48:32 2016 oddou_f
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
  if (str != NULL)
    {
      shell_commands_free(shell);
      if (parser_control(shell, str) == false)
	shell->last_return = EXIT_FAILURE;
      free(str);
      shell_list_treat(shell);
      shell_commands_free(shell);
    }
}

bool			shell_get_commands(t_shell		*shell)
{
  char			*str;

  shell_prompt(shell);
  while ((str = get_next_line(STDIN_FILENO)) != NULL)
    {
      shell_step(shell, str);
      shell_prompt(shell);
    }
  return (true);
}
