/*
** main.c for main in /
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 10:57:32 2016 Frederic ODDOU
** Last update Sun May 01 22:33:52 2016 oddou_f
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

int		main(int ac, char **av, char **ae)
{
  t_shell	shell;

  shell_signal(true);
  if (shell_init(&shell, ac, av, ae) == false)
    return (EXIT_FAILURE);
  shell_get_commands(&shell);
  shell_close(&shell, EXIT_SUCCESS);
  return (EXIT_SUCCESS);
}
