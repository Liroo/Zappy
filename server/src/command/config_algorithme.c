/*
** config_algorithme.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Fri Jun 23 02:57:54 2017 guicha_t
** Last update Fri Jun 23 03:05:56 2017 guicha_t
*/

#include "game.h"
#include "struct.h"
#include "h.h"

int	get_config_vector(int x, int y, int xmax, int ymax)
{
  int   positive_x;
  int   positive_y;

  if (x < 0)
    positive_x = -x;
  else
    positive_x = x;
  if (y < 0)
    positive_y = -y;
  else
    positive_y = y;
  if (positive_x < xmax && positive_y < ymax)
    return (1);
  else if (positive_x < xmax && ymax < positive_y)
    return (2);
  else if (xmax < positive_x && positive_y < ymax)
    return (3);
  else if (xmax < positive_x && ymax < positive_y)
    return (4);
  return (0);
}

int	get_dir_config_one(int x, int y)
{
  int   positive_x;
  int   positive_y;

  if (x < 0)
    positive_x = -x;
  else
    positive_x = x;
  if (y < 0)
    positive_y = -y;
  else
    positive_y = y;
  if (positive_x > positive_y)
    {
      if (x > 0)
	return (W);
      else
	return (E);
    }
  else
    {
      if (y > 0)
	return (S);
      else
	return (N);
    }
}

int	get_dir_config_two(int x, int ymax, int send_y, int dest_y)
{
  int   positive_x;

  if (x < 0)
    positive_x = -x;
  else
    positive_x = x;
  if (positive_x > ymax)
    {
      if (x < 0)
	return (W);
      else
	return (E);
    }
  else
    {
      if (send_y > dest_y)
	return (S);
      else
	return (N);
    }
}

int	get_dir_config_three(int xmax, int y, int sendx, int destx)
{
  int   positive_y;

  if (y < 0)
    positive_y = -y;
  else
    positive_y = y;

  if (positive_y > xmax)
    {
      if (y > 0)
	return (S);
      else
	return (N);
    }
  else
    {
      if (sendx > destx)
	return (W);
      else
	return (E);
    }
}

int	get_dir_config_four(int x, int y, t_player *s, t_player *d)
{
  if (x > y)
    {
      if (s->pos_x > d->pos_x)
	return (W);
      else
	return (E);
    }
  else
    {
      if (s->pos_y > d->pos_y)
	return (S);
      else
	return (N);
    }
}
