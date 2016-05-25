/*
** del.c for del in /lib/getch/src/rd/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Wed May 25 14:44:32 2016 John Doe
** Last update Wed May 25 14:44:39 2016 John Doe
*/

#include "rd.h"

int     		rd_del(t_rd *rd, int key)
{
  (void)key;
  rd_rm_char(RD_LINE, rd->curs);
  rd_disp(rd);
  return (0);
}
