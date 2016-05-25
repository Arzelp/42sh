/*
** ctrl_l.c for ctrl_l in /lib/getch/src/rd/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Wed May 25 14:26:23 2016 John Doe
** Last update Wed May 25 14:28:55 2016 John Doe
*/

#include <stdio.h>
#include "rd.h"

int     rd_ctrl_l(t_rd *rd, int key)
{
  (void)key;
  printf("\e[1;1H\e[2J");
  fflush(stdout);
  rd_disp(rd);
  return (0);
}
