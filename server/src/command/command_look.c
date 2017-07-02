/*
** look.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 21 22:49:06 2017 Thomas
** Last update Sun Jul  2 05:55:54 2017 Pierre Monge
*/

#include <stdio.h>

#include "struct.h"
#include "chrono.h"
#include "game.h"
#include "debug.h"
#include "h.h"
#include "rfc.h"
#include "log.h"

static void	send_vertical_look(t_client *client, int distance,
				   int dir, int dir_x)
{
  int		x;
  int		y;
  int		end_y;
  t_player	*player;

  player = client->data;
  x = player->pos_x + (dir_x * distance);
  y = player->pos_y - (dir * distance);
  end_y = player->pos_y + (dir * distance) + dir;
  while (y != end_y)
    {
      queue_packet(client, SIMPLE_PACKET, ",");
      print_tiles(client, x, y);
      y += dir;
    }
}

static void	send_horizontal_look(t_client *client, int distance,
				   int dir, int dir_y)
{
  int		x;
  int		end_x;
  int		y;
  t_player	*player;

  player = client->data;
  x = player->pos_x - (dir * distance);
  end_x = player->pos_x + (dir * distance) + dir;
  y = player->pos_y + (dir_y * distance);
  while (x != end_x)
    {
      queue_packet(client, SIMPLE_PACKET, ",");
      print_tiles(client, x, y);
      x += dir;
    }
}

static void	get_tiles_line_object(t_client *client, int dir_x,
				      int dir_y, int distance)
{
  int		dir;
  t_player	*player;

  player = client->data;
  dir = player->direction == 1 || player->direction == 2 ?
    -1 : 1;
  if (dir_x != 0)
    send_vertical_look(client, distance, dir, dir_x);
  else
    send_horizontal_look(client, distance, dir, dir_y);
}

int	cmd_look(t_client *client, char *token)
{
  t_player	*player;
  int		dir_x;
  int		dir_y;
  int		distance;

  (void)token;
  player = client->data;
  dir_x = (player->direction % 2 == 1) ? (player->direction - 2) * -1 : 0;
  dir_y = (player->direction % 2 == 0) ? (player->direction - 1) * -1 : 0;
  distance = 1;
  queue_packet(client, SIMPLE_PACKET, "[");
  print_tiles(client, player->pos_x, player->pos_y);
  while (distance <= player->elevation)
    {
      get_tiles_line_object(client, dir_x, dir_y, distance);
      distance++;
    }
  queue_packet(client, SIMPLE_PACKET, "]\n");
  print_log("Player %d from %s: LOOK\n",
	    client->net_info.fd,
	    player->team->name);
  rfc_08(NULL, client);
  return (0);
}
