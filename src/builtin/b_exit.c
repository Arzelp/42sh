/*
** b_exit.c for exit in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 15:07:40 2016 Frederic ODDOU
** Last update Thu May 05 15:25:44 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

static int		b_exit_error(char		*str)
{
  int		i;

  i = 0;
  if (str[i] != '\0' && str[i] == '-')
    i++;
  while (str[i] != '\0')
    {
      if (!(str[i] >= '0' && str[i] <= '9'))
	{
	  printf("exit: Expression Syntax.\n");
	  return (EXIT_FAILURE);
	}
      i++;
    }
  if (i == 1 && str[0] == '-')
    {
      printf("exit: Expression Syntax.\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int			b_exit(int			ac,
			       char			**av,
			       t_shell			*shell)
{
  unsigned char		ret;

  ret = EXIT_SUCCESS;
  if (ac > 2)
    {
      printf("exit: Expression Syntax.\n");
      return (EXIT_FAILURE);
    }
  if (ac > 1)
    {
      if (b_exit_error(av[1]) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      ret = my_atoi(av[1]);
    }
  shell_commands_free(shell);
  shell_close(shell, ret);
  printf("exit\n");
  return (EXIT_FAILURE);
}
