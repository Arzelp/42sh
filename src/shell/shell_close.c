/*
** shell_close.c for close in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:33 2016 Frederic ODDOU
** Last update Wed May 18 13:19:32 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"
#include "utils.h"

bool		shell_close(t_shell		*shell,
			    unsigned char	value)
{
  if (shell->oldpwd != NULL)
    free(shell->oldpwd);
  shell_commands_free(shell);
  utils_locales_delete_list(shell->locales);
  my_tab_free(shell->path);
  my_tab_free(shell->ae);
  exit(value);
}
