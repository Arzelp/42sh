/*
** loop.c for wolf in /home/josso/en_cours/wolf_swag
** 
** Made by Arthur Josso
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Fri Apr 29 17:46:22 2016 Arthur Josso
** Last update Fri Apr 29 17:49:54 2016 Arthur Josso
*/

#include <ncurses.h>
#include "wolf.h"

static int      key_listener(t_win *win)
{
  int           key;

  key = getch();
  if (key == 27)
    return (1);
  if (key == 'w')
    move_cam(win, FORWARD);
  if (key == 's')
    move_cam(win, BACKWARD);
  if (key == 'a')
    move_cam(win, LEFT);
  if (key == 'd')
    move_cam(win, RIGHT);
  if (key == KEY_LEFT)
    go_left(win);
  if (key == KEY_RIGHT)
    go_right(win);
  return (0);
}

static int      alloc_pix_array(t_win *win)
{
  int           h;
  int           w;

  getmaxyx(stdscr, h, w);
  if (!h || !w)
    return (1);
  if ((win->array = bunny_new_pixelarray(w, 2 * h)) == NULL)
    return (1);
  return (0);
}

static t_color  get_term_color(t_bunny_pixelarray *pix, t_bunny_position p)
{
  t_color       c1;
  t_color       c2;

  p.y *= 2;
  c1 = get_pixel(pix, &p);
  p.y++;
  c2 = get_pixel(pix, &p);
  c1.argb[RED_CMP] = (c1.argb[RED_CMP] + c2.argb[RED_CMP]) / 2;
  c1.argb[BLUE_CMP] = (c1.argb[BLUE_CMP] + c2.argb[BLUE_CMP]) / 2;
  c1.argb[GREEN_CMP] = (c1.argb[GREEN_CMP] + c2.argb[GREEN_CMP]) / 2;
  c1.argb[RED_CMP] /= 51;
  c1.argb[BLUE_CMP] /= 51;
  c1.argb[GREEN_CMP] /= 51;
  return (c1);
}

static void             blit_on_term(t_bunny_pixelarray *pix)
{
  t_color               c;
  t_bunny_position      p;
  int                   color;

  p.y = 0;
  while (p.y < pix->clipable.clip_height / 2)
    {
      p.x = 0;
      while (p.x < pix->clipable.clip_width)
	{
	  c = get_term_color(pix, p);
	  color = COLOR(c.argb[RED_CMP], c.argb[GREEN_CMP], c.argb[BLUE_CMP]) + 1;
	  attron(COLOR_PAIR(color));
	  mvaddch(p.y, p.x, ' ');
	  attroff(COLOR_PAIR(color));
	  p.x++;
	}
      p.y++;
    }
}

int      main_loop(t_win *win, int *quit)
{
  while (!(*quit))
    {
      if (alloc_pix_array(win) == 1)
	return (1);
      if (set_torch(win->array, &win->texture.torch) == 1
	  || set_heart(win->array, &win->texture.heart) == 1)
	return (1);
      *quit = key_listener(win);
      set_ground(win);
      draw_wall(win);
      draw_sprite(win->array, &win->texture.torch);
      draw_sprite(win->array, &win->texture.heart);
      blit_on_term(win->array);
      bunny_delete_clipable(&win->array->clipable);
    }
  return (0);
}
