/*
** wolf.h for wolf3d in /home/josso_a/rendu/info/gfx_wolf3d
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Thu Dec  3 18:28:54 2015 Tetra
** Last update Wed Jun  1 14:57:41 2016 Arthur Josso
*/

#pragma once

#include <lapin.h>

#define SEG	(2.5)
#define D	(3.5)
#define MOVE	(0.05)
#define ROT	(2)

#define RAD(deg) ((deg) * M_PI / 180)
#define MAP(x, ba, ea, bb, eb) ((((ba - x) / (ba - ea)) * (eb - bb)) + bb)
#define COLOR(r, g, b) (36 * (r) + 6 * (g) + (b))

typedef struct	s_cols
{
  t_color	sky;
  t_color	wall;
  t_color	ground;
}		t_cols;

typedef struct	s_me
{
  float		x;
  float		y;
  float		ratio;
  int		a;
  char		wall_type;
}		t_me;

typedef struct	s_map
{
  int		height;
  int		width;
  char		**map;
}		t_map;

typedef struct		s_sprite
{
  int			width;
  int			nb_frame;
  float			act_frame;
  t_bunny_position	beg;
  t_bunny_position	end;
  t_bunny_pixelarray	*pix;
}			t_sprite;

typedef struct		s_texture
{
  t_bunny_pixelarray	*wall;
  t_bunny_pixelarray	*sky;
  t_bunny_pixelarray	*door;
  t_sprite		torch;
  t_sprite		heart;
}			t_texture;

typedef struct		s_win
{
  t_bunny_window	*win;
  t_bunny_pixelarray	*array;
  t_me			me;
  t_map			map;
  t_cols		cols;
  t_texture		texture;
}			t_win;

int	main_loop(t_win *win, int *quit);

/*
** wolf.c
*/

int	draw_wall(t_win *win);

/*
** tekpixel.c
*/

void		tekpixel(t_bunny_pixelarray *pix,
			 t_bunny_position *p,
			 t_color *c);

t_color         get_pixel(t_bunny_pixelarray *pix,
			  t_bunny_position *pos);

unsigned int	tekgetpixel(t_bunny_pixelarray *pix,
			    t_bunny_position *p);

/*
** default_map.c
*/

int	set_def_map(t_win *win);
void    free_map(t_map *map);

/*
** move.c
*/

typedef enum	e_move
  {
    FORWARD	= 0,
    BACKWARD	= 1,
    LEFT	= 2,
    RIGHT	= 3
  }		t_move;

void    move_cam(t_win *win, char move);
void	go_left(t_win *win);
void	go_right(t_win *win);

/*
** get_data.c
*/

int	set_data(const char *path,
		 const char *scope,
		 t_win *win);

/*
** lib.c
*/

void    my_putstr(char *s);
int     my_strlen(const char *str);
int     my_strcmp(const char *s1, const char *s2);
int     my_getnbr(const char *str);

/*
** get_var.c
*/

void    set_xy(t_win *win, float *x1, float *y1, float x);
float   get_k(float a, float a0, float va);
float	get_x(t_win *win, float k, float va, float a0);
float	get_y(t_win *win, float k, float va, float a0);

/*
** wall_color.c
*/

void    set_cols(t_win *win);
void	put_in_black(t_bunny_pixelarray *pix);
void	set_ground(t_win *win);
void	fill_wall(t_win *win,
		  t_bunny_pixelarray *wall,
		  t_bunny_position *pos,
		  float k);

/*
** err.c
*/

int     err(char *s);
int	check(t_win *win);

/*
** sprites
*/

void    draw_sprite(t_bunny_pixelarray *pix, t_sprite *sprite);
int     set_torch(t_bunny_pixelarray *pix, t_sprite *torch);
int     set_heart(t_bunny_pixelarray *pix, t_sprite *heart);

/*
** load_bmp.c
*/

typedef struct		s_bmp
{
  unsigned short	magic;
  unsigned int		size;
  unsigned int		none;
  unsigned int		start;
  unsigned int		header_size;
  unsigned int		width;
  unsigned int		height;
  unsigned short	nb_plan;
  unsigned short	bpp;
  unsigned int		compression;
  unsigned int		img_size;
  unsigned int		ppm_width;
  unsigned int		ppm_height;
  unsigned int		nb_col_pal;
  unsigned int		nb_col_imp;
} __attribute__ ((packed)) t_bmp;

t_bunny_pixelarray      *load_bitmap(const char *file);
