/*
** utils_get_var.c for utils get var in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 21:32:58 2016 Frederic ODDOU
** Last update Wed May 11 14:03:53 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

#define DELIM_VAR_OPEN	'{'
#define DELIM_VAR_CLOSE	'}'

static int		utils_get_acolade_count(char		*find)
{
  int			i;

  i = 0;
  if (*find != DELIM_VAR_OPEN)
    return (-1);
  while (find[i] != '\0')
    {
      if (find[i] == DELIM_VAR_CLOSE)
	return (i);
      i++;
    }
  return (-1);
}

static char		*utils_get_acolade(char			*find)
{
  char			*new;
  int			i;

  i = 0;
  if ((new = malloc(sizeof(char) * (utils_get_acolade_count(find) + 1))) == NULL)
    return (NULL);
  while (find[i + 1] != '\0' && find[i + 1] != DELIM_VAR_CLOSE)
    {
      new[i] = find[i + 1];
      i++;
    }
  new[i] = '\0';
  return (new);
}

static char		*utils_get_var_find(t_shell		*shell,
					    char		*find)
{
  char			*var;
  t_locales		*loc;

  loc = shell->locales;
  if ((var = b_getenv(shell->ae, find)) != NULL)
    return (var);
  while (loc != NULL)
    {
      if (!strcmp(loc->name, find))
	return (loc->value);
      loc = loc->next;
    }
  fprintf(stderr, "%s: Undefined variable.\n", find);
  return (NULL);
}

static char		*my_str_realloc(char			*s1,
					char			*s2)
{
  size_t		len;

  if (s1 == NULL || s2 == NULL)
    return (NULL);
  len = strlen(s1) + strlen(s2);
  s1 = realloc(s1, sizeof(char) * (len + 1));
  s1 = strcat(s1, s2);
  return (s1);
}

static char		*utils_parse_var(t_shell		*shell,
					 char			*str)
{
  int			i;
  char			*new;
  char			*find;
  char			*var;
  char			c[2];

  i = 0;
  if ((new = malloc(sizeof(char))) == NULL)
    return (NULL);
  *new = '\0';
  memset(c, '\0', 2);
  while (str[i] != '\0')
    {
      find = NULL;
      if (str[i] == '$')
	{
	  if (utils_get_acolade_count(&str[i + 1]) != -1)
	    find = utils_get_acolade(&str[i + 1]);
	  if ((var = utils_get_var_find(shell, (find != NULL) ? find : &str[i + 1])) == NULL)
	    {
	      free(new);
	      return (NULL);
	    }
	  i += ((find != NULL) ? (utils_get_acolade_count(&str[i + 1]) + 2) : (int)strlen(&str[i])) - 1;
	  new = my_str_realloc(new, var);
	  if (find != NULL)
	    free(find);
	}
      else
	{
	  *c = str[i];
	  new = my_str_realloc(new, c);
	}
      i++;
    }
  return (new);
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
  if (strstr(commands->str, "$"))
    {
      if (!strncmp(commands->str, "$?", 2))
	return (utils_get_var_return(shell, commands));
      return (utils_parse_var(shell, commands->str));
    }
  if (!strncmp(commands->str, "~", 1))
    return (utils_get_homepath(commands));
  return (commands->str);
}
