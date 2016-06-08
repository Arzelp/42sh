/*
** tekpixel.c for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec  3 19:42:46 2015 Tetra
** Last update Thu Dec  3 19:43:11 2015 Tetra
*/

#include <lapin.h>

void    tekpixel(t_bunny_pixelarray *pix,
		 t_bunny_position *p,
		 t_color *c)
{
  if (p->x >= 0 && p->x < pix->clipable.clip_width &&
      p->y >= 0 && p->y < pix->clipable.clip_height)
  ((unsigned int*)pix->pixels)[p->y * pix->clipable.clip_width + p->x]
    = c->full;
}
