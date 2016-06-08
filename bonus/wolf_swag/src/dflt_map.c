/*
** default_map.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Dec  7 17:08:01 2015 Tetra
** Last update Sun Dec 13 17:29:20 2015 Tetra
*/

#include "wolf.h"

char	*my_strdup(char *s)
{
  char	*str;
  int	size;
  int	i;

  size = my_strlen(s);
  if ((str = bunny_malloc(size + 1)) == NULL)
    return (NULL);
  i = 0;
  while (i < size)
    {
      str[i] = s[i];
      i++;
    }
  str[i] = '\0';
  return (str);
}

int	set_def_map(t_win *win)
{
  int	i;

  i = 0;
  win->map.height = 8;
  win->map.width = 9;
  if ((win->map.map = bunny_malloc(win->map.width * sizeof(char*))) == NULL)
    return (1);
  win->map.map[0] = my_strdup("11111111");
  win->map.map[1] = my_strdup("10000001");
  win->map.map[2] = my_strdup("10000001");
  win->map.map[3] = my_strdup("10000001");
  win->map.map[4] = my_strdup("10001001");
  win->map.map[5] = my_strdup("10000001");
  win->map.map[6] = my_strdup("10000001");
  win->map.map[7] = my_strdup("10000001");
  win->map.map[8] = my_strdup("11111111");
  while (i < win->map.width)
    if (win->map.map[i++] == NULL)
      return (1);
  win->me.x = 2;
  win->me.y = 2;
  win->me.a = 45;
  return (0);
}

void	free_map(t_map *map)
{
  int	i;

  i = 0;
  while (i < map->width)
    bunny_free(map->map[i++]);
  bunny_free(map->map);
}
