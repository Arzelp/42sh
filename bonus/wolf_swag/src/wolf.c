/*
** wolf.c for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec  3 20:40:00 2015 Tetra
** Last update Fri Apr 29 17:06:26 2016 Arthur Josso
*/

#include <math.h>
#include "wolf.h"

void	test_x(t_win *win, float vx, float vy, float *k_min)
{
  int	i;
  int   back;
  float k;
  float	y;
  char	wall_type;

  i = 0;
  while (vx != 0 && i < win->map.width)
    {
      back = 0;
      k = get_k(i, win->me.x, vx);
      y = get_y(win, k, vy, win->me.y);
      if (win->me.x >= i)
	back = 1;
      if (y != -1 && i - back != -1
	  && (wall_type = win->map.map[(int)i - back][(int)y]) != '0'
	  && k >= 0 && k < *k_min)
	{
	  *k_min = k;
	  win->me.ratio = back != 1 ? 1 - (y - (int)y) : y - (int)y;
	  win->me.wall_type = wall_type;
	}
      i++;
    }
}

void    test_y(t_win *win, float vx, float vy, float *k_min)
{
  int   i;
  int   back;
  float k;
  float	x;
  char	wall_type;

  i = 0;
  while (vy != 0 && i < win->map.height)
    {
      back = 0;
      k = get_k(i, win->me.y, vy);
      x = get_x(win, k, vx, win->me.x);
      if (win->me.y >= i)
	back = 1;
      if (x != -1 && i - back != -1
	  && (wall_type = win->map.map[(int)x][(int)i - back]) != '0'
	  && k >= 0 && k < *k_min)
	{
	  *k_min = k;
	  win->me.ratio = back == 1 ? 1 - (x - (int)x) : x - (int)x;
	  win->me.wall_type = wall_type;
	}
      i++;
    }
}

float	set_k(t_win *win, float vx, float vy)
{
  float k_min;

  k_min = win->map.height + win->map.width;
  test_x(win, vx, vy, &k_min);
  test_y(win, vx, vy, &k_min);
  return (k_min);
}

void			wall_gen(t_win *win, t_bunny_position *pos, float k)
{
  t_bunny_position	p;
  t_color		col;
  int			w_y2;

  w_y2 = win->array->clipable.clip_height / 2;
  if (pos->y < (w_y2) - k)
    {
      p.y = MAP((float)pos->y, 0.0, (float)w_y2,
		0.0, (float)win->texture.sky->clipable.clip_height);
      p.x = MAP((float)pos->x, 0.0, (float)win->array->clipable.clip_width,
		0.0, (float)win->texture.sky->clipable.clip_width);
      col.full = tekgetpixel(win->texture.sky, &p);
      tekpixel(win->array, pos, &col);
    }
  else if (w_y2 - k <=  pos->y && pos->y <= w_y2 + k)
    {
      if (win->me.wall_type == '1')
	fill_wall(win, win->texture.wall, pos, k);
      else if (win->me.wall_type == '2')
	fill_wall(win, win->texture.door, pos, k);
    }
  pos->y++;
}

int			draw_wall(t_win *win)
{
  t_bunny_position	pos;
  float			vx;
  float			vy;
  float			k;

  pos.x = 0;
  while (pos.x < win->array->clipable.clip_width)
    {
      set_xy(win, &vx, &vy, pos.x);
      k = set_k(win, vx, vy);
      k *= sqrt(vx * vx + vy * vy);
      k = win->array->clipable.clip_height / k;
      k /= 2;
      pos.y = 0;
      while (pos.y < win->array->clipable.clip_height)
	wall_gen(win, &pos, k);
      pos.x++;
    }
  return (0);
}
