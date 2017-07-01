/*
** config_algorithme.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Fri Jun 23 02:57:54 2017 guicha_t
** Last update Sat Jul  1 01:41:19 2017 guicha_t
*/

#include "debug.h"
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
  if (positive_x <= xmax && positive_y <= ymax)
    return (1);
  else if (positive_x <= xmax && ymax <= positive_y)
    return (2);
  else if (xmax <= positive_x && positive_y <= ymax)
    return (3);
  else if (xmax <= positive_x && ymax <= positive_y)
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
    if (x >= 0)
      return (W);
    else
      return (E);
  else
    if (y > 0)
      return (S);
    else
      return (N);
}

int	get_dir_config_two(int x, int ymax, int send_y, int dest_y)
{
  int   positive_x;

  if (x < 0)
    positive_x = -x;
  else
    positive_x = x;
  if (dest_y > send_y)
    if (positive_x > ymax)
      if (x < 0)
	return (E);
      else
	return (W);
    else
      return (N);
  else
    if (positive_x > ymax)
      if (x < 0)
	return (E);
      else
	return (W);
    else
      return (S);
}

int	get_dir_config_three(int xmax, int y, int send_x, int dest_x)
{
  int   positive_y;

  if (y < 0)
    positive_y = -y;
  else
    positive_y = y;
  if (dest_x > send_x)
    if (positive_y > xmax)
      if (y < 0)
	return (N);
      else
	return (S);
    else
      return (E);
  else
    if (xmax < positive_y)
      if (y < 0)
	return (N);
      else
	return (S);
    else
      return (W);
}

int	get_dir_config_four(int x, int y, t_player *s, t_player *d)
{
  if (d->pos_x > s->pos_x && d->pos_y > s->pos_y)
    if (x > y)
      return (E);
    else
      return (N);
  else if (d->pos_x > s->pos_x && d->pos_y < s->pos_y)
    if (x > y)
      return (E);
    else
      return (S);
  else if (d->pos_x < s->pos_x && d->pos_y < s->pos_y)
    if (x > y)
      return (W);
    else
      return (S);
  else
    if (x > y)
      return (W);
    else
      return (N);
}
