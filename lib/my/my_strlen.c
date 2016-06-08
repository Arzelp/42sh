/*
** my_strlen.c for strlen in /home/oddou_f/Documents/Epitech/B2-Systeme-Unix/PSU_2015_42sh/lib/my/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Wed Jun  8 11:46:03 2016 Frederic ODDOU
** Last update Wed Jun  8 11:48:26 2016 Frederic ODDOU
*/

#include <string.h>

int		my_strlen(const char *str)
{
  int		len;

  len = (int)strlen(str);
  if (len < 0)
    return (0);
  return (len);
}
