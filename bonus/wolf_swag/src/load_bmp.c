/*
** load_bmp.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d/bonus
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec 10 18:48:21 2015 Tetra
** Last update Sat Dec 12 20:59:18 2015 Tetra
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "wolf.h"

int                     get_pixels(t_bmp *img, int fd, t_bunny_pixelarray *pix)
{
  t_color               col;
  t_color               buff;
  t_bunny_position      pos;
  int                   i;
  int                   size;

  size = img->width * img->height;
  pos.x = -1;
  pos.y = -1;
  i = 0;
  while (read(fd, &col, sizeof(t_color)) > 0 && i < size)
    {
      buff = col;
      col.argb[3] = buff.argb[0];
      col.argb[0] = buff.argb[3];
      col.argb[1] = buff.argb[2];
      col.argb[2] = buff.argb[1];
      pos.x = i % img->width;
      pos.y = img->height - i / img->width - 1;
      tekpixel(pix, &pos, &col);
      i++;
    }
  if (pos.x != (int)img->width - 1 || pos.y)
    return (1);
  return (0);
}

t_bunny_pixelarray      *load_bitmap(const char *file)
{
  t_bunny_pixelarray    *array;
  int                   fd;
  t_bmp                 header;
  int                   len;
  char			bin[128];

  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  if ((len = read(fd, &header, sizeof(t_bmp))) <= 0)
    return (NULL);
  if (read(fd, bin, header.start - len) == -1)
    return (NULL);
  if ((array = bunny_new_pixelarray(header.width, header.height)) == NULL)
    return (NULL);
  if (get_pixels(&header, fd, array) == 1)
    return (NULL);
  close(fd);
  return (array);
}
