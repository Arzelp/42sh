/*
** shell_init.c for init in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:01 2016 Frederic ODDOU
** Last update Thu Apr 28 12:52:06 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

bool		shell_init(t_shell		*shell,
			   int			ac,
			   char			**av,
			   char			**ae)
{
  (void)ac;
  (void)av;
  if ((shell->ae = my_tab_cpy(ae)) == NULL)
    return (false);
  shell->commands = NULL;
  shell->list = NULL;
  return (true);
}
