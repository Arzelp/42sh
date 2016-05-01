/*
** my_tab_realloc.c for realloc in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:53:13 2016 Frederic ODDOU
** Last update Sat Apr 30 21:18:59 2016 oddou_f
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my.h"

bool		my_tab_realloc(char	**tab,
			       char	*str)
{
  int		len;

  if ((len = my_tab_len(tab)) == -1)
    return (false);
  if (realloc(tab, sizeof(char *) * (len + 2)) == NULL)
    return (false);
  tab[len] = str;
  tab[len + 1] = NULL;
  return (true);
}
