/*
** lib.c for fdf in /home/josso_a/lib.c
** 
** Made by josso_a
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Wed Nov 11 13:09:56 2015 josso_a
** Last update Fri Dec 11 18:24:08 2015 Tetra
*/

#include <unistd.h>

int	my_strlen(const char *str)
{
  int	i;

  i = 0;
  while (str[i] != 0)
    i++;
  return (i);
}

void    my_putstr(char *s)
{
  write(1, s, my_strlen(s));
}

int	my_strcmp(const char *s1, const char *s2)
{
  int	i;

  i = 0;
  while (!(s1[i] == 0 || s2[i] == 0))
    {
      if (s1[i] < s2[i])
	return (-1);
      else if (s1[i] > s2[i])
	return (1);
      i++;
    }
  if (s1[i] == 0 && s2[i] != 0)
    return (-1);
  else if (s2[i] == 0 && s1[i] != 0)
    return (1);
  else
    return (0);
}

long    my_getnbr(const char *str)
{
  int   size;
  long  result;
  int   i;
  long	mult;

  result = 0;
  mult = 1;
  size = my_strlen(str) - 1;
  i = size;
  while (i >= 0)
    {
      if (str[i] >= '0' && str[i] <= '9')
	result += mult * (str[i] - '0');
      else if (str[i] == '-' && i == 0 && str[i + 1])
	result *= -1;
      else
	{
	  my_putstr("error on get_nbr()\n");
	  return (0);
	}
      mult *= 10;
      i--;
    }
  return (result);
}
