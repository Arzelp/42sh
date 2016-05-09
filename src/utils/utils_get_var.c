/*
** utils_get_var.c for utils get var in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 21:32:58 2016 Frederic ODDOU
** Last update Mon May 09 22:11:21 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "parser.h"

static char		*utils_get_var_find(t_shell		*shell,
					    t_commands		*commands)
{
  char			*var;
  t_locales		*loc;

  loc = shell->locales;
  if ((var = b_getenv(shell->ae, &commands->str[1])) != NULL)
    return (var);
  while (loc != NULL)
    {
      if (!strcmp(loc->name, &commands->str[1]))
	return (loc->value);
      loc = loc->next;
    }
  return (&commands->str[1]);
}

static char		*utils_get_var_return(t_shell		*shell,
					      t_commands	*commands)
{
  free(commands->str);
  if ((commands->str = malloc(sizeof(char) * 4)) == NULL)
    return (NULL);
  commands->str = memset(commands->str, '\0', 4);
  snprintf(commands->str, 4, "%d", shell->last_return);
  return (commands->str);
}

char			*utils_get_var(t_shell			*shell,
				       t_commands		*commands)
{
  if (GET_ID(commands->index_delim) == ID_SIMPLE_QUOTE)
    return (commands->str);
  if (commands->str == NULL)
    return (NULL);
  if (!strncmp(commands->str, "$", 1))
    {
      if (!strncmp(commands->str, "$?", 2))
	return (utils_get_var_return(shell, commands));
      return (utils_get_var_find(shell, commands));
    }
  return (commands->str);
}
