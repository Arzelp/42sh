/*
** get_line.c for get line in /
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Wed Jan 13 21:49:09 2016 Frederic ODDOU
** Last update Wed Jan 13 21:49:09 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char			*get_cat(char *str,
				 char *buffer,
				 long len,
				 long size)
{
  long			i1;
  long			i2;
  char			*new;

  i1 = 0;
  i2 = 0;
  if ((len + size + 1) > 0 &&
      (new = malloc(sizeof(char) * (len + size))) == NULL)
    return (NULL);
  while (i1 < len)
    {
      new[i1] = str[i1];
      i1++;
    }
  while (i2 < size)
    new[i1++] = buffer[i2++];
  if (len > 0)
    free(str);
  return (new);
}

long			get_first_n(char *str, long len)
{
  long			i;

  i = 0;
  while (i < len)
    {
      if (str[i] == '\n')
	return (i);
      i++;
    }
  return (-1);
}

char			*get_new(char *str, long deb, long end)
{
  char			*new;
  long			i;

  i = 0;
  if (((end - deb) + 1) > 0 &&
      (new = malloc(sizeof(char) * ((end - deb) + 1))) == NULL)
    return (NULL);
  while (deb < end)
    new[i++] = str[deb++];
  new[i] = '\0';
  return (new);
}

char			*get_str(const int fd,
				 char *str,
				 long *len,
				 long *back)
{
  char			buffer[READ_SIZE];
  long			size;

  str = (*len == 0) ? "" : str;
  while ((*back = get_first_n(str, *len)) == -1)
    {
      if ((size = read(fd, buffer, READ_SIZE)) <= 0)
	{
	  if (*len > 0)
	    {
	      *back = *len;
	      return (str);
	    }
	  return (NULL);
	}
      if ((str = get_cat(str, buffer, *len, size)) == NULL)
	return (NULL);
      *len += size;
    }
  return (str);
}

char			*get_next_line(const int fd)
{
  static long		len;
  static char		*str;
  long			back;
  char			*new;
  char			*ret;

  if ((str = get_str(fd, str, &len, &back)) == NULL)
    return (NULL);
  if ((ret = get_new(str, 0, back)) == NULL)
    return (NULL);
  if ((len - (back + 1)) > 0)
    {
      new = get_new(str, back + 1, len);
      free(str);
      str = new;
    }
  else
    free(str);
  len -= (back + 1);
  return (ret);
}
