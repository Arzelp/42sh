/*
** shell_init.c for init in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 17:30:01 2016 Frederic ODDOU
** Last update Sat May 21 11:26:42 2016 oddou_f
*/

#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "builtin.h"
#include "shell.h"

static void	shell_init_path(t_shell		*shell)
{
  char		*path;

  path = b_getenv(shell->ae, "PATH");
  if (path == NULL)
    path = DEFAULT_PATH;
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
  shell_init_path(shell);
  shell->pid.pid = getpid();
  if ((shell->pid.pgid = getpgid(shell->pid.pid)) == -1)
    return (false);
  if (getcwd(oldpwd, 4096) == NULL)
    strcpy(oldpwd, "/");
  shell->oldpwd = strdup(oldpwd);
  return (true);
}
