/*
** shell_close.c for close in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:33 2016 Frederic ODDOU
** Last update Sat Apr 23 17:30:33 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

bool		shell_close(t_shell		*shell,
			    unsigned char	value)
{
  my_tab_free(shell->ae);
  exit(value);
}
