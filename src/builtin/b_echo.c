/*
** b_echo.c for echo in /src/builtin/
**
** Made by Frederic ODDOU
** Login   <oddou_f@frederic.oddou@epitech.eu>
**
** Started on  Wed May 25 23:18:31 2016 Frederic ODDOU
** Last update Wed May 25 23:33:26 2016 Frederic ODDOU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "my.h"

typedef struct s_echo_flag
{
  char	*str;
  char	c;
}		t_echo_flag;

static t_echo_flag    g_echo_tab[] =
{
    {"\a", 'a'},
    {"\b", 'b'},
    {"\t", 't'},
    {"\n", 'n'},
    {"\v", 'v'},
    {"\f", 'f'},
    {"\r", 'r'},
    {"x", 'x'},
    {"\0", '0'},
    {0, 0}
};

static char	*null_case(char	src)
{
  char		*res;

  if ((res = malloc(2 * sizeof(char))) == NULL)
    return (NULL);
  res[0] = src;
  res[1] = '\0';
  return (res);
}

char	*my_strcat_char(char *dest, char src)
{
  char	*res;
  int	i;
  int	len;

  i = 0;
  if (dest == NULL)
    return (null_case(src));
  len = strlen(dest);
  if ((res = malloc((len + 2) * sizeof(char))) == NULL)
    return (NULL);
  res[0] = '\0';
  while (dest[i] != '\0')
    {
      res[i] = dest[i];
      i++;
    }
  res[i] = src;
  res[i + 1] = '\0';
  free(dest);
  return (res);
}

static long int	echo_calc(char *str, long int i)
{
  char		*nb;
  long int	tmp;

  tmp = i;
  if (str[i] == '\0')
    return (i);
  nb = NULL;
  while (str[i] >= '0' && str[i] <= '9')
    {
      if ((nb = my_strcat_char(nb, str[i])) == NULL)
	return (i);
      i++;
    }
  if (str[tmp - 1] == 'x')
    printf("%c", (int)strtol(nb, NULL, 16));
  if (str[tmp - 1] == '0')
    printf("%c", (int)strtol(nb, NULL, 8));
  free(nb);
  return (i);
}

char		*get_elem_from_tab(char c)
{
  long int	i;

  i = 0;
  while (g_echo_tab[i].str != NULL)
    {
      if (g_echo_tab[i].c == c)
	return (g_echo_tab[i].str);
      i++;
    }
  return (NULL);
}

static long int	check_param(char *str, char param)
{
  long int	i;

  if (str[0] != '-' && param == 'n')
    return (EXIT_FAILURE);
  else if (str[0] != '-' && param == 'e')
    return (EXIT_FAILURE);
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == param)
	return (EXIT_SUCCESS);
      i++;
    }
  return (EXIT_FAILURE);
}

static void	print(char *str, char *first_arg)
{
  long int	i;
  char		*type;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '\\' && check_param(first_arg, 'e') == EXIT_SUCCESS &&
	  (type = get_elem_from_tab(str[i + 1])) != NULL)
	{
	  if (str[i + 1] == 'x' || str[i + 1] == '0')
	    i = echo_calc(str, i + 2);
	  else
	    {
	      printf("%s", type);
	      i += 2;
	    }
	}
      else
	{
	  printf("%c", str[i]);
	  i++;
	}
    }
}

int			b_echo(int			ac,
			       char			**av,
			       t_shell			*shell)
{
  long int	i;

  if (!shell->write)
    return (EXIT_SUCCESS);
  if (ac == 1)
    {
      printf("\n");
      return (0);
    }
  i = 1;
  while (av[i] != NULL)
    {
      if ((i == 1 && av[i][0] != '-' ) || i != 1)
	print(av[i], av[1]);
      if (av[i][0] != '-' && av[i + 1] != NULL)
	printf(" ");
      i++;
    }
  if (av[1] != NULL && check_param(av[1], 'n') == EXIT_FAILURE)
    printf("\n");
  return (EXIT_SUCCESS);
}
