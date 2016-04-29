/*
** my_tab_delete_elem.c for my tab delete in /lib/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 23 16:46:21 2016 Frederic ODDOU
** Last update Sat Apr 23 16:46:21 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "my.h"

bool		my_tab_delete_elem(char	**tab,
				   char	*str)
{
  int		i;
  int		j;
  int		len;

  i = 0;
  j = 0;
  if ((len = my_tab_len(tab)) == -1)
    return (NULL);
  while (tab[i] != NULL)
    {
      if (tab[i] != str)
	j++;
      tab[i] = tab[j];
      i++;
    }
  tab[i] = NULL;
  free(str);
  if (realloc(tab, sizeof(char *) * len) == NULL)
    return (false);
  return (true);
}
