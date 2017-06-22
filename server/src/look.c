/*
** look.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 21 22:49:06 2017 Thomas
** Last update Thu Jun 22 05:55:54 2017 Thomas
*/

#include "struct.h"
#include "h.h"

static int	get_range_per_elevation(t_player *p)
{
  int		range;

  range = 0;
  if (p->elevation < '2')
    range = 1;
  else if (p->elevation < '3')
    range = 2;
  else
    range = 3;
  return (range);
}

static void	get_directional_position(t_player *p, int *x, int *y)
{
  if (p->direction == 0)
    *y = -1;
  else if (p->direction == 1)
    *x = 1;
  else if (p->direction == 2)
    *y = 1;
  else
    *x = -1;
}

static void	get_tiles_line_object(t_player *p, int dir_x, int dir_y, int range)
{
  int		begin_direction;

  if (p->direction == 0 || p->direction == 1)
    begin_direction = -1;
  else
    begin_direction = 1;
  if (dir_x == 0)
    send_vertical_look(p, range, begin_direction, dir_y);
  else if (dir_y == 0)
    send_horizontal_look(p, range, begin_direction, dir_x);
}

int	cmd_look(t_player *p, char *token)
{
  int		range;
  int		dir_x;
  int		dir_y;
  int		i;

  (void)token;
  i = 0;
  dir_x = 0;
  dir_y = 0;
  range = get_range_per_elevation(p);
  get_directional_position(p, &dir_x, &dir_y);
  queue_packet(p, SIMPLE_PACKET, "[");
  while (i <= range)
    {
      get_tiles_line_object(p, dir_x * i, dir_y * i, i);
      i++;
    }
  queue_packet(p, SIMPLE_PACKET, "]\n");
  return (0);
}
