/*
** torch.c for wolf in /home/josso_a/rendu/info/gfx_wolf3d/bonus
** 
** Made by Tetra
** Login   <arthur.josso@epitech.eu>
** 
** Started on  Sat Dec 12 15:00:37 2015 Tetra
** Last update Fri Apr 29 17:55:25 2016 Arthur Josso
*/

#include "wolf.h"

void			sprite_loop(t_bunny_pixelarray *pix,
				    t_sprite *sprite,
				    int beg,
				    int end)
{
  t_bunny_position      pos;
  t_bunny_position      p;
  t_color               col;
  t_color               teal;

  teal.full = TEAL;
  teal.argb[ALPHA_CMP] = 0;
  pos.y = sprite->beg.y;
  while (pos.y < sprite->end.y)
    {
      pos.x = sprite->beg.x;
      while (pos.x < sprite->end.x)
	{
	  p.x = MAP((float)pos.x, sprite->beg.x, sprite->end.x, beg, end);
	  p.y = MAP((float)pos.y, sprite->beg.y, sprite->end.y, 0,
		    sprite->pix->clipable.clip_height);
	  if ((col.full = tekgetpixel(sprite->pix, &p)) != teal.full)
	    tekpixel(pix, &pos, &col);
	  pos.x++;
	}
      pos.y++;
    }
}

void	draw_sprite(t_bunny_pixelarray *pix, t_sprite *sprite)
{
  int	beg;
  int	end;

  beg = (int)sprite->act_frame * sprite->width;
  end = sprite->width * ((int)sprite->act_frame + 1);
  sprite_loop(pix, sprite, beg, end);
  sprite->act_frame += 0.1;
  if (sprite->act_frame >= sprite->nb_frame)
    sprite->act_frame = 0;
}

int     set_heart(t_bunny_pixelarray *pix, t_sprite *heart)
{
  heart->width = 112;
  heart->beg.x = 7 * pix->clipable.clip_width / 10;
  heart->beg.y = 4 * pix->clipable.clip_height / 6;
  heart->end.x = 9 * pix->clipable.clip_width / 10;
  heart->end.y = pix->clipable.clip_height;
  return (0);
}

int	set_torch(t_bunny_pixelarray *pix, t_sprite *torch)
{
  torch->width = 200;
  torch->beg.x = 0;
  torch->beg.y = pix->clipable.clip_height / 2;
  torch->end.x = 2 * pix->clipable.clip_width / 5;
  torch->end.y = pix->clipable.clip_height;
  return (0);
}
