/*
** b_set.c for set in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 12:44:31 2016 Frederic ODDOU
** Last update Wed May 18 17:05:20 2016 oddou_f
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"

static int		b_set_treat(char			**av,
				    t_shell			*shell)
{
  char			*reponse[2];
  t_locales		*loc;

  reponse[0] = NULL;
  reponse[1] = NULL;
  if (utils_tab_fusion(av, reponse) == false)
    return (EXIT_FAILURE);
  if (reponse[0] == NULL || strlen(reponse[0]) <= 0)
    {
      free(reponse[0]);
      return (EXIT_FAILURE);
    }
  if ((loc = utils_locales_find_elem(reponse[0], shell->locales)) != NULL)
    {
      free(loc->name);
      if (loc->value != NULL)
	free(loc->value);
      loc->name = reponse[0];
      loc->value = reponse[1];
    }
  else
    shell->locales = utils_locales_add_left(reponse, shell->locales);
  return (EXIT_SUCCESS);
}

int			b_set(int				ac,
			      char				**av,
			      t_shell				*shell)
{
  (void)ac;
  if (utils_if_fusion(&av[1]) == true)
    return (b_set_treat(&av[1], shell));
  else
    {
      if (shell->write)
	fprintf(stdout, "[Usage] set name=value\n");
    }
  return (EXIT_FAILURE);
}
