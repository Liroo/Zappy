/*
** get_value_algorithme.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Fri Jun 23 03:06:29 2017 guicha_t
** Last update Fri Jun 23 03:07:12 2017 guicha_t
*/

#include "h.h"
#include "struct.h"

int	get_diff_max_x(t_player *send, t_player *dest)
{
  int   res;

  if (dest->pos_x > send->pos_x)
    res = (game.map_size_x - dest->pos_x) + send->pos_x;
  else
    res = (game.map_size_x - send->pos_x) + dest->pos_x;
  return (res);
}

int	get_diff_max_y(t_player *send, t_player *dest)
{
  int   res;

  if (dest->pos_y > send->pos_y)
    res = (game.map_size_y - dest->pos_y) + send->pos_y;
  else
    res = (game.map_size_y - send->pos_y) + dest->pos_y;
  return (res);
}
