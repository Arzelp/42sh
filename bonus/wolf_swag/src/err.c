/*
** err.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Dec  8 10:36:06 2015 Tetra
** Last update Sun Dec 13 17:32:27 2015 Tetra
*/

#include "wolf.h"

int	err(char *s)
{
  my_putstr(s);
  return (-1);
}

int			check_valid(t_win *win)
{
  t_bunny_position      p;

  p.x = 0;
  while (p.x < win->map.width)
    {
      p.y = 0;
      while (p.y < win->map.height)
	{
	  if (win->map.map[p.x][p.y] != '1' && win->map.map[p.x][p.y] != '0'
	      && win->map.map[p.x][p.y] != '2')
	    return (err("Invalid map\n"));
	  p.y++;
	}
      p.x++;
    }
  if (win->me.x < 0 || win->me.x >= win->map.width
      || win->me.y < 0 || win->me.y >= win->map.height)
    return (err("You're not spawning on the map...\n"));
  return (0);
}

int                     check(t_win *win)
{
  t_bunny_position      p;

  if (check_valid(win) == -1)
    return (-1);
  p.x = 0;
  while (p.x < win->map.width)
    {
      if (win->map.map[p.x][0] != '1' ||
	  win->map.map[p.x][win->map.height - 1] != '1')
	return (err("Hole in the wall !\n"));
      p.x++;
    }
  p.y = 0;
  while (p.y < win->map.height)
    {
      if (win->map.map[0][p.y] != '1' ||
	  win->map.map[win->map.width - 1][p.y] != '1')
	return (err("Hole in the wall !\n"));
      p.y++;
    }
  if (win->map.map[(int)win->me.x][(int)win->me.y] == '1')
    return (err("You're spawning in a wall...\n"));
  return (0);
}
