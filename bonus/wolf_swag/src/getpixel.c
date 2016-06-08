/*
** tekgetpixel.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d/bonus
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec 10 21:53:31 2015 Tetra
** Last update Fri Dec 11 15:37:56 2015 Tetra
*/

#include "wolf.h"

unsigned int    tekgetpixel(t_bunny_pixelarray *pix,
			    t_bunny_position *pos)
{
  if (pos->x >= 0 && pos->x < pix->clipable.clip_width &&
      pos->y >= 0 && pos->y < pix->clipable.clip_height)
    return (((unsigned int*)pix->pixels)
	    [pos->y * pix->clipable.clip_width + pos->x]);
  return (0);
}
