/*
** parser_commands.c for commands in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Apr 27 10:32:16 2016 Frederic ODDOU
** Last update Fri Apr 29 16:27:40 2016 oddou_f
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "parser.h"

/*
** On essai de savoir si la chaine correspond à un de nos délimiteurs
*/
static short		parser_type_delimit(char		*str,
					    int			*n)
{
  short			id_delimit;

  id_delimit = 0;
  while (GET_TYPE(id_delimit) != ID_WITHOUT)
    {
      if (!strncmp(&str[*n], g_parser_delimit[id_delimit].delimit,
		   strlen(g_parser_delimit[id_delimit].delimit)))
	return (id_delimit);
      id_delimit++;
    }
  return (ID_WITHOUT);
}

/*
** On essaie de chercher la fin d'un délimiteur.
** Par exemple pour "(", on fait toute la chaine jusqu'au premier ")"
** Sinon c'est une erreur
*/
static bool		parser_find_end(char			*str,
					char			*end,
					int			*i)
{
  while (str[*i] != '\0')
    {
      if (!strncmp(&str[*i], end, strlen(end)))
	return (true);
      *i += 1;
    }
  return (false);
}

/*
** Dans le cas où il y a un délimiteur, on passe sur cette fonction
** Si c'est une commande à garder comme les rédirection ou separateur on prend
** Si c'est un délimiteur on va chercher jusqu'où il se termine
*/
static bool		parser_not_without(t_shell		*shell,
					   char			*str,
					   int			*i,
					   int			id_delimit)
{
  int			deb;

  *i += strlen(g_parser_delimit[id_delimit].delimit);
  deb = *i;
  if (GET_TYPE(id_delimit) == D_GET || IF_SEP(id_delimit))
    shell->commands = utils_commands_add_right(shell->commands,
					       NULL,
					       id_delimit);
  else if (GET_TYPE(id_delimit) == D_DELIM)
    {
      if (parser_find_end(str, g_parser_delimit[id_delimit].end, i))
	{
	  shell->commands = utils_commands_add_right(shell->commands,
						     strndup(&str[deb],
							     *i - deb),
						     id_delimit);
	  *i += strlen(g_parser_delimit[id_delimit].end);
	}
      else
	{
	  printf(ERR_UNMATCH, g_parser_delimit[id_delimit].end);
	  return (false);
	}
    }
  return (true);
}

bool			parser_commands(t_shell			*shell,
					char			*str)
{
  int			i;
  int			deb;
  int			id_delimit;

  i = 0;
  shell->commands = NULL;
  while (str[i] != '\0')
    {
      deb = i;
      while (str[i] != '\0' &&
	     (id_delimit = parser_type_delimit(str, &i)) == ID_WITHOUT)
	i++;
      if (i - deb > 0)
	shell->commands = utils_commands_add_right(shell->commands,
						   strndup(&str[deb], i - deb),
						   ID_WITHOUT);
      if (id_delimit != ID_WITHOUT)
	{
	  if (parser_not_without(shell, str, &i, id_delimit) == false)
	    return (false);
	}
    }
  shell->commands = utils_commands_go_back(shell->commands);
  return (true);
}