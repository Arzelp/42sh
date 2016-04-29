/*
** main.c for main in /
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 10:57:32 2016 Frederic ODDOU
** Last update Sat Apr 16 10:57:32 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "shell.h"

void		shell_signaux()
{
  signal(SIGQUIT, SIG_IGN);
  if (isatty(STDIN_FILENO))
    {
      signal(SIGINT, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGCHLD, SIG_IGN);
      signal(SIGTERM, SIG_IGN);
    }
}

int		main(int ac, char **av, char **ae)
{
  t_shell	shell;

  shell_signaux();
  if (shell_init(&shell, ac, av, ae) == false)
    return (1);
  shell_get_commands(&shell);
  shell_close(&shell, 0);
  return (0);
}
