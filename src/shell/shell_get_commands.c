/*
** shell_get_commands.c for shell_get_commands in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:38:22 2016 Frederic ODDOU
** Last update Thu Apr 28 15:23:58 2016 oddou_f
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "shell.h"
#include "parser.h"

bool			shell_get_commands(t_shell	*shell)
{
  char			*str;

  printf("?> ");
  fflush(stdout);
  while ((str = get_next_line(0)) != NULL)
    {
      parser_control(shell, str);
      free(str);
      printf("?> ");
      fflush(stdout);
    }
  return (true);
}
