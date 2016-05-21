/*
** utils_history.c for history in /src/utils/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat May 21 21:24:10 2016 Frederic ODDOU
** Last update Sat May 21 21:49:55 2016 oddou_f
*/

#include <stdlib.h>
#include "shell.h"

t_past			*utils_history_add_right(t_past		*history,
						char		*str)
{
  t_past		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = NULL;
  new->str = str;
  new->prev = history;
  new->id = 1;
  if (history != NULL)
    {
      new->id = history->id + 1;
      history->next = new;
    }
  return (new);
}

t_past			*utils_history_go_back(t_past		*past)
{
  while (past != NULL && past->prev != NULL)
    past = past->prev;
  return (past);
}

void			utils_history_delete_elem(t_past	*history)
{
  if (history->next != NULL)
    history->next->prev = history->prev;
  if (history->prev != NULL)
    history->prev->next = history->next;
  if (history->str != NULL)
    free(history->str);
  free(history);
}

void			utils_history_delete_list(t_past	*history)
{
  t_past		*tmp;

  history = utils_history_go_back(history);
  while (history != NULL)
    {
      tmp = history;
      history = history->next;
      if (tmp->str != NULL)
	free(tmp->str);
      free(tmp);
    }
}
