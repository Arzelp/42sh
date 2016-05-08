/*
** shell_prompt.c for prompt in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun May  8 18:29:17 2016 Frederic ODDOU
** Last update Sun May 08 18:31:39 2016 oddou_f
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"

void			shell_prompt(t_shell			*shell)
{
  if (isatty(STDIN_FILENO))
    {
      printf("?> ");
      fflush(stdout);
    }
  (void)shell;
}
