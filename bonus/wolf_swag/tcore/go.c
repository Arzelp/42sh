/*
** go.c for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Fri Dec  4 23:11:29 2015 Tetra
** Last update Sun Dec  6 22:02:00 2015 Tetra
*/

#include <lapin.h>
#include <math.h>

void	go(t_bunny_position *curpos,
	   double angle,
	   t_bunny_position *newpos,
	   int move)
{
  newpos->x = (float)move * cos(angle) + curpos->x;
  newpos->y = (float)move * sin(angle) + curpos->y;
}
