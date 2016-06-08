/*
** get_var.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Mon Dec  7 19:38:35 2015 Tetra
** Last update Fri Apr 29 16:40:11 2016 Arthur Josso
*/

#include <math.h>
#include "wolf.h"

void    set_xy(t_win *win, float *x1, float *y1, float x)
{
  float x2;
  float y2;

  *x1 = D;
  *y1 = (SEG * (win->array->clipable.clip_width / 2 - x)) /
    win->array->clipable.clip_width;
  x2 = (*x1) * cos(RAD(win->me.a)) - (*y1) * sin(RAD(win->me.a));
  y2 = (*x1) * sin(RAD(win->me.a)) + (*y1) * cos(RAD(win->me.a));
  *x1 = x2;
  *y1 = y2;
}

float   get_k(float a, float a0, float va)
{
  return ((a - a0) / va);
}

float	get_x(t_win *win, float k, float va, float a0)
{
  float result;

  result = k * va + a0;
  if (result >= win->map.width || result < 0)
    result = -1;
  return (result);
}

float	get_y(t_win *win, float k, float va, float a0)
{
  float result;

  result = k * va + a0;
  if (result >= win->map.height || result < 0)
    result = -1;
  return (result);
}
