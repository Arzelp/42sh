/*
** b_alias.c for set in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed May 18 12:44:31 2016 Frederic ODDOU
** Last update Mon May 23 15:44:46 2016 oddou_f
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "utils.h"
#include "my.h"

static int		b_alias_treat(char			**av,
				      t_shell			*shell)
{
  char			*reponse[2];
  char			**tab_to;

  reponse[0] = NULL;
  reponse[1] = NULL;
  if (utils_tab_fusion(av, reponse))
    {
      tab_to = my_str_to_wordtab(reponse[1], ' ');
      tab_to = utils_alias_replace(shell, tab_to, true);
      shell->alias = utils_alias_add_left(shell->alias,
					  my_str_to_wordtab(reponse[0], ' '),
					  tab_to);
      free(reponse[0]);
      free(reponse[1]);
      return (EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

int			b_alias(int				ac,
				char				**av,
				t_shell				*shell)
{
  (void)ac;
  if (utils_if_fusion(&av[1]) == true)
    return (b_alias_treat(&av[1], shell));
  else
    {
      if (shell->write)
	fprintf(stdout, "[Usage] alias command=replace\n");
    }
  return (EXIT_FAILURE);
}
