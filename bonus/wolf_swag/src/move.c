/*
** move.c for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Dec  7 13:55:26 2015 Tetra
** Last update Fri Apr 29 16:46:35 2016 Arthur Josso
*/

#include <math.h>
#include "wolf.h"

void	get_next_pos(t_me *me, char move)
{
  if (move == FORWARD)
    {
      me->x += MOVE * cos(RAD(me->a));
      me->y += MOVE * sin(RAD(me->a));
    }
  else if (move == LEFT)
    {
      me->x += MOVE * cos(RAD(me->a) + M_PI / 2);
      me->y += MOVE * sin(RAD(me->a) + M_PI / 2);
    }
  else if (move == RIGHT)
    {
      me->x += MOVE * cos(RAD(me->a) - M_PI / 2);
      me->y += MOVE * sin(RAD(me->a) - M_PI / 2);
    }
  else if (move == BACKWARD)
    {
      me->x += MOVE * cos(RAD(me->a) + M_PI);
      me->y += MOVE * sin(RAD(me->a) + M_PI);
    }
}

void    move_cam(t_win *win, char move)
{
  float x0;
  float x1;
  float y0;
  float y1;

  x0 = win->me.x;
  y0 = win->me.y;
  get_next_pos(&win->me, move);
  x1 = win->me.x;
  y1 = win->me.y;
  get_next_pos(&win->me, move);
  if (win->map.map[(int)win->me.x][(int)y1] != '1')
    win->me.x = x1;
  else
    win->me.x = x0;
  if (win->map.map[(int)x1][(int)win->me.y] != '1')
    win->me.y = y1;
  else
    win->me.y = y0;
}

void	go_left(t_win *win)
{
  win->me.a += ROT;
  if (win->me.a >= 360)
    win->me.a %= 360;
}

void	go_right(t_win *win)
{
  win->me.a -= ROT;
  if (win->me.a < 0)
    win->me.a += 360;
}
