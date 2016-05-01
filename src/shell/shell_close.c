/*
** shell_close.c for close in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:33 2016 Frederic ODDOU
** Last update Fri Apr 29 23:53:09 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

bool		shell_close(t_shell		*shell,
			    unsigned char	value)
{
  shell_commands_free(shell);
  my_tab_free(shell->path);
  my_tab_free(shell->ae);
  exit(value);
}
