/*
** algorithme_vector.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 22 21:43:46 2017 guicha_t
** Last update Tue Jun 27 00:31:47 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"
#include "game.h"
#include "h.h"

int	check_same_line_col(t_player *p_send, t_player *p_dest)
{
  if (p_send->pos_x == p_dest->pos_x &&
      p_send->pos_y == p_dest->pos_y)
    {
      // same tile
      PRINT_DEBUG("Broadcast [same tile]\n");
      return (0);
      // WARNING
    }
  else if (p_send->pos_x == p_dest->pos_x)
    {
      PRINT_DEBUG("Broadcast [same column]\n");
      if (p_send->pos_y > p_dest->pos_y)
	return (N);
      else
	return (S);
    }
  else if (p_send->pos_y == p_dest->pos_y)
    {
      PRINT_DEBUG("Broadcast [same line]\n");
      if (p_send->pos_x > p_dest->pos_x)
	return (E);
      else
	return (W);
    }
  return (0);
}

int	check_same_diagonal(t_player *p_send, t_player *p_dest)
{
  int	diff_x;
  int	diff_y;

  diff_x = p_send->pos_x - p_dest->pos_x;
  diff_y = p_send->pos_y - p_dest->pos_y;
  if (diff_x > 0 && diff_x == diff_y)
    return (NE);
  else if (diff_x > 0 && diff_x == -diff_y)
    return (SE);
  else if (diff_x < 0 && diff_x == diff_y)
    return (SW);
  else if (diff_x < 0 && diff_x == -diff_y)
    return (NW);
  return (0);
}

int	harmless_vector(t_player *send, t_player *dest)
{
  int	diff_x;
  int	diff_y;
  int	diff_max_x;
  int	diff_max_y;
  int	config;
  int	dir;

  diff_x = dest->pos_x - send->pos_x;
  diff_y = dest->pos_y - send->pos_y;
  diff_max_x = get_diff_max_x(send, dest);
  diff_max_y = get_diff_max_y(send, dest);
  config = get_config_vector(diff_x, diff_y, diff_max_x, diff_max_y);
  if (config == 1)
    dir = get_dir_config_one(diff_x, diff_y);
  else if (config == 2)
    dir = get_dir_config_two(diff_x, diff_max_y,
			     send->pos_y, dest->pos_y);
  else if (config == 3)
    dir = get_dir_config_three(diff_max_x, diff_y,
			       send->pos_x, dest->pos_x);
  else
    dir = get_dir_config_four(diff_max_x, diff_max_y,
			      send, dest);
  return (dir);
}

int	algorithme_vector(t_player *p_send, t_player *p_dest)
{
  int	dir;

  dir = check_same_line_col(p_send, p_dest);
  if (dir == 0)
    dir = check_same_diagonal(p_send, p_dest);
  if (dir != 0)
    PRINT_DEBUG("Broadcast [same diago]\n");
  if (dir == 0)
    dir = harmless_vector(p_send, p_dest);
  PRINT_DEBUG("Broadcast Dir : %d\n", dir);
  return (dir);
}
