/*
** parser_commands_backslash.c for commands backslash in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 20:50:28 2016 Frederic ODDOU
** Last update Mon May 09 21:41:10 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "parser.h"

static void		parser_commands_purge_str(char		*str)
{
  int			i;

  i = 0;
  while (str[i] != '\0')
    {
      str[i] = str[i + 1];
      i++;
    }
}

static void		parser_commands_purge(t_commands	*commands)
{
  int			i;

  i = 0;
  if (commands->str == NULL)
    return ;
  while (commands->str[i] != '\0')
    {
      if (!strncmp(g_parser_delimit[commands->index_delim].end,
		   &commands->str[i],
		   strlen(g_parser_delimit[commands->index_delim].end)))
	{
	  if (i > 0 && commands->str[i - 1] == '\\')
	    parser_commands_purge_str(&commands->str[i - 1]);
	}
      i++;
    }
}

void			parser_commands_backslash(t_commands	*commands)
{
  while (commands != NULL)
    {
      if (GET_TYPE(commands->index_delim) == D_DELIM)
	parser_commands_purge(commands);
      commands = commands->next;
    }
}
