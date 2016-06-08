/*
** vecnorm.c for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec  3 21:52:22 2015 Tetra
** Last update Mon Dec  7 16:07:25 2015 Tetra
*/

#include <lapin.h>
#include <math.h>

double		vecnorm(t_bunny_position *coord0,
			t_bunny_position *coord1)
{
  double	ret;

  ret = sqrt((coord1->x - coord0->x) * (coord1->x - coord0->x)
	     + (coord1->y - coord0->y) * (coord1->y - coord0->y));
  return (ret);
}
