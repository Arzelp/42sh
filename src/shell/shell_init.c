/*
** shell_init.c for init in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:01 2016 Frederic ODDOU
** Last update Sat May 21 21:39:34 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "builtin.h"
#include "shell.h"

static void	shell_init_path(t_shell		*shell)
{
  char		*path;
  char		buffer[4096];

  path = b_getenv(shell->ae, "PATH");
  if (path == NULL)
    {
      memset(buffer, '\0', 4096);
      confstr(_CS_PATH, buffer, 4096);
      shell->path = my_str_to_wordtab(buffer, ':');
    }
  else
    shell->path = my_str_to_wordtab(path, ':');
}

bool		shell_init(t_shell		*shell,
			   int			ac,
			   char			**av,
			   char			**ae)
{
  char		oldpwd[4096];

  (void)ac;
  (void)av;
  if ((shell->ae = my_tab_cpy(ae)) == NULL)
    return (false);
  shell->commands = NULL;
  shell->list = NULL;
  shell->locales = NULL;
  shell->last_return = 0;
  shell->fd[FD_IN] = STDIN_FILENO;
  shell->fd[FD_OUT] = STDOUT_FILENO;
  shell->write = false;
  shell->alias = NULL;
  shell->jobs = NULL;
  shell->history = NULL;
  shell_init_path(shell);
  shell->pid.pid = getpid();
  if ((shell->pid.pgid = getpgid(shell->pid.pid)) == -1)
    return (false);
  if (getcwd(oldpwd, 4096) == NULL)
    strcpy(oldpwd, "/");
  shell->oldpwd = strdup(oldpwd);
  return (true);
}
