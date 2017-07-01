/*
** look.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 21 22:49:06 2017 Thomas
** Last update Sat Jul  1 05:07:32 2017 guicha_t
*/

#include <stdio.h>

#include "struct.h"
#include "chrono.h"
#include "game.h"
#include "debug.h"
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

void		get_directional_position(t_player *p, int *x, int *y)
{
  if (p->direction == 0)
    *y = 1;
  else if (p->direction == 1)
    *x = 1;
  else if (p->direction == 2)
    *y = -1;
  else
    *x = -1;
}

static void	get_tiles_line_object(t_client *client, int dir_x,
				      int dir_y, int range)
{
  int		begin_direction;
  t_player	*p;

  p = client->data;
  if (p->direction == 0 || p->direction == 1)
    begin_direction = -1;
  else
    begin_direction = 1;
  if (dir_x == 0)
    send_vertical_look(client, range, begin_direction, dir_y);
  else if (dir_y == 0)
    send_horizontal_look(client, range, begin_direction, dir_x);
}

int	cmd_look(t_client *client, char *token)
{
  t_player	*p;
  int		range;
  int		dir_x;
  int		dir_y;
  int		i;

  (void)token;
  p = client->data;
  i = 0;
  dir_x = 0;
  dir_y = 0;
  range = get_range_per_elevation(p);
  get_directional_position(p, &dir_x, &dir_y);
  queue_packet(client, SIMPLE_PACKET, "[");
  while (i <= range)
    {
      get_tiles_line_object(client, dir_x * i, dir_y * i, i);
      i++;
    }
  queue_packet(client, SIMPLE_PACKET, "]\n");
  return (0);
}
