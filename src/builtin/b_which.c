/*
** b_which.c for which in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 14:44:42 2016 Frederic ODDOU
** Last update Thu May 05 15:00:01 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"

int			b_which(int			ac,
				char			**av,
				t_shell			*shell)
{
  int			i;
  char			*str;

  if (ac < 2)
    {
      printf("which: Too few arguments.\n");
      return (EXIT_FAILURE);
    }
  i = 1;
  while (av[i] != NULL)
    {
      if (b_is_builtin(av[i]) != NOT_BUILTIN)
	printf("%s: shell built-in command.\n", av[i]);
      else if ((str = shell_get_path(shell, av[i])) != NULL)
	{
	  printf("%s\n", str);
	  free(str);
	}
      i++;
    }
  return (EXIT_SUCCESS);
}
