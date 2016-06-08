/*
** get_data.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Dec  7 16:33:19 2015 Tetra
** Last update Sun Dec 13 17:23:37 2015 Tetra
*/

#include "wolf.h"

int             set_size(t_bunny_ini *file, const char *scope, t_map *map)
{
  const char    *buff;

  if ((buff = bunny_ini_get_field(file, scope, "width", 0)) == NULL)
    return (err("Error on width\n"));
  map->width = my_getnbr(buff);
  if ((buff = bunny_ini_get_field(file, scope, "height", 0)) == NULL)
    return (err("Error on height\n"));
  map->height = my_getnbr(buff);
  return (0);
}

int             set_map(t_bunny_ini *file, const char *scope, t_map *map)
{
  int           i;
  int		j;
  const char    *buff;

  if ((map->map = bunny_malloc(map->width * sizeof(char*))) == NULL)
    return (-1);
  i = 0;
  while (i < map->width)
    if ((map->map[i++] = bunny_malloc(map->height)) == NULL)
      return (-1);
  j = 0;
  while (j < map->height)
    {
      i = 0;
      while (i < map->width)
	{
	  if ((buff = bunny_ini_get_field
	       (file, scope, "data", j * map->width + i)) == NULL)
	    return (err("Error on map\n"));
	  map->map[i][j] = buff[0];
	  i++;
	}
      j++;
    }
  return (0);
}

int		set_me(t_bunny_ini *file, const char *scope, t_me *me)
{
  const char    *buff;
  int		i;

  i = 0;
  while (i < 3)
    {
      if ((buff = bunny_ini_get_field(file, scope, "start_position", i))
	  == NULL)
	return (err("Error start position\n"));
      if (i == 0)
	me->x = my_getnbr(buff) + 0.5;
      if (i == 1)
	me->y = my_getnbr(buff) + 0.5;
      if (i == 2)
	me->a = my_getnbr(buff);
      i++;
    }
  return (0);
}

int             set_data(const char *path, const char *scope, t_win *win)
{
  t_bunny_ini   *file;

  if ((file = bunny_load_ini(path)) == NULL)
    return (-1);
  if (set_size(file, scope, &win->map) == -1)
    return (-1);
  if (set_map(file, scope, &win->map) == -1)
    return (-1);
  if (set_me(file, scope, &win->me) == -1)
    return (-1);
  bunny_delete_ini(file);
  if (check(win) == -1)
    return (-1);
  return (0);
}
