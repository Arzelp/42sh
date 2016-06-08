/*
** my_getpixel.c for rt in /home/josso/rendu/gfx/gfx_raytracer1
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Feb 16 18:52:01 2016 Arthur Josso
** Last update Tue Feb 16 18:52:02 2016 Arthur Josso
*/

#include <lapin.h>

t_color		get_pixel(t_bunny_pixelarray *pix,
			  t_bunny_position *pos)
{
  t_color       color;

  if (pos->x >= 0 && pos->x < pix->clipable.clip_width &&
      pos->y >= 0 && pos->y < pix->clipable.clip_height)
    color.full = ((unsigned int*)pix->pixels)
      [pos->y * pix->clipable.clip_width + pos->x];
  else
    color.full = 0;
  return (color);
}
