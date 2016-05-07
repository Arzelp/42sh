/*
** b_unsetenv.c for unsetenv in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 14:28:19 2016 Frederic ODDOU
** Last update Fri May 06 11:56:15 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int			b_unsetenv(int			ac,
				   char			**av,
				   t_shell		*shell)
{
  int			i;
  char			*str;

  if (ac < 2)
    {
      printf(FEW_ARG, av[0]);
      return (EXIT_FAILURE);
    }
  i = 1;
  while (av[i] != NULL)
    {
      if ((str = b_findenv(shell->ae, av[i])) != NULL)
	{
	  if ((shell->ae = my_tab_delete_elem(shell->ae, str)) == NULL)
	    return (ERROR_FATAL);
	  if (!strcmp(av[i], "PATH"))
	    {
	      my_tab_free(shell->path);
	      shell->path = NULL;
	    }
	}
      i++;
    }
  return (EXIT_SUCCESS);
}
