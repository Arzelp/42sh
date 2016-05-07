/*
** b_is_builtin.c for if builtin in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 30 22:30:55 2016 Frederic ODDOU
** Last update Fri May 06 00:04:54 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "builtin.h"

short			b_is_builtin(char		*name)
{
  short			i;

  i = 0;
  while (g_builtin[i].name != NULL)
    {
      if (strcmp(g_builtin[i].name, name) == 0)
	{
	  if (g_builtin[i].func != NULL)
	    return (i);
	}
      i++;
    }
  return (NOT_BUILTIN);
}
