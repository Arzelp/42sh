/*
** shell_prompt_func.c for prompt func in /src/shell/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Tue May 24 13:37:39 2016 John Doe
** Last update Tue May 24 23:51:06 2016 John Doe
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include "shell.h"
#include "utils.h"

void			shell_prompt_directory(t_shell		*shell)
{
  char			pwd[4096];

  (void)shell;
  if (getcwd(pwd, 4096) == NULL)
    strcpy(pwd, "/");
  printf("%s", pwd);
}

void			shell_prompt_nb_line(t_shell		*shell)
{
  if (shell->history)
    printf("%u", shell->history->id + 1);
  else
    printf("1");
}

void			shell_prompt_ret_value(t_shell		*shell)
{
  printf("%hd", shell->last_return);
}

void			shell_prompt_version(t_shell		*shell)
{
  (void)shell;
  printf("FreddouSH");
}

void			shell_prompt_user(t_shell		*shell)
{
  struct passwd		*pws;

  (void)shell;
  if ((pws = getpwuid(geteuid())) == NULL)
    return ;
  printf("%s", pws->pw_name);
}