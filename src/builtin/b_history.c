/*
** b_history.c for env in /src/builtin/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu May  5 13:40:11 2016 Frederic ODDOU
** Last update Sat May 21 21:44:58 2016 oddou_f
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"

int			b_history(int			ac,
				  char			**av,
				  t_shell		*shell)
{
  t_past		*history;

  history = shell->history;
  history = utils_history_go_back(history);
  if (!shell->write)
    return (EXIT_SUCCESS);
  while (history != NULL)
    {
      printf("%u\t%s\n", history->id, history->str);
      history = history->next;
    }
  (void)ac;
  (void)av;
  return (EXIT_SUCCESS);
}
