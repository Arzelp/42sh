/*
** main.c for fdf in /home/josso_a/rendu/info/gfx_fdf1/src
** 
** Made by josso_a
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Tue Nov 10 14:16:13 2015 josso_a
** Last update Wed Jun  1 15:32:34 2016 Arthur Josso
*/

#include <ncurses.h>
#include "wolf.h"

static void	init_cols()
{
  int		r;
  int		g;
  int		b;
  int		i;

  r = -1;
  while (++r < 6)
    {
      g = -1;
      while (++g < 6)
	{
	  b = -1;
	  while (++b < 6)
	    {
	      i = COLOR(r, g, b);
	      init_color(i, 200 * r, 200 * g, 200 * b);
	      init_pair(i + 1, i, i);
	    }
	}
    }
}

static int	init(t_win *win)
{
  win->texture.heart.nb_frame = 6;
  win->texture.heart.act_frame = 0;
  if ((win->texture.heart.pix = load_bitmap("ressources/heart.bmp")) == NULL)
    return (1);
  win->texture.torch.nb_frame = 7;
  win->texture.torch.act_frame = 0;
  if ((win->texture.torch.pix = load_bitmap("ressources/torch.bmp")) == NULL)
    return (1);
  if ((win->texture.wall = load_bitmap("ressources/wall.bmp")) == NULL)
    return (1);
  if ((win->texture.sky = load_bitmap("ressources/night.bmp")) == NULL)
    return (1);
  if ((win->texture.door = load_bitmap("ressources/door.bmp")) == NULL)
    return (1);
  initscr();
  start_color();
  if (!has_colors() || !can_change_color())
    return (err("Cannot change your term's colors\n"));
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  init_cols();
  curs_set(0);
  refresh();
  return (0);
}

static void	exit_cleaner(t_win *win)
{
  free_map(&win->map);
  bunny_delete_clipable(&win->texture.wall->clipable);
  bunny_delete_clipable(&win->texture.sky->clipable);
  bunny_delete_clipable(&win->texture.door->clipable);
  bunny_delete_clipable(&win->texture.heart.pix->clipable);
  bunny_delete_clipable(&win->texture.torch.pix->clipable);
  endwin();
}

int	main(int ac, char **av)
{
  t_win	win;
  int	quit;

  if (init(&win) == 1)
    return (1);
  if (ac == 2 && set_data(av[1], "level1", &win) == -1)
    return (1);
  else if (ac != 2 && set_def_map(&win) == 1)
    return (1);
  set_cols(&win);
  quit = 0;
  if (main_loop(&win, &quit) == 1)
    return (1);
  exit_cleaner(&win);
  return (0);
}
