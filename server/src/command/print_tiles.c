/*
** print_tiles.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Thu Jun 22 05:27:01 2017 Thomas
** Last update Sun Jul  2 05:48:42 2017 Pierre Monge
*/

#include <stdio.h>

#include "struct.h"
#include "h.h"

static void	print_tiles_next(t_client *client, int x, int y)
{
  int		i;
  i = -1;
  while (++i < (int)game.map[x][y].linemate)
    queue_packet(client, SIMPLE_PACKET, " linemate");
  i = -1;
  while (++i < (int)game.map[x][y].deraumere)
    queue_packet(client, SIMPLE_PACKET, " deraumere");
  i = -1;
  while (++i < (int)game.map[x][y].sibur)
    queue_packet(client, SIMPLE_PACKET, " sibur");
  i = -1;
  while (++i < (int)game.map[x][y].mendiane)
    queue_packet(client, SIMPLE_PACKET, " mendiane");
  i = -1;
  while (++i < (int)game.map[x][y].phiras)
    queue_packet(client, SIMPLE_PACKET, " phiras");
  i = -1;
  while (++i < (int)game.map[x][y].thystame)
    queue_packet(client, SIMPLE_PACKET, " thystame");
  i = -1;
  while (++i < (int)game.map[x][y].food)
    queue_packet(client, SIMPLE_PACKET, " food");
}

void	print_tiles(t_client *client, int x, int y)
{
  int		i;
  t_player      *p;

  p = client->data;
  i = 0;
  if (x < 0)
    x += game.map_size_x;
  else if (x >= (int)game.map_size_x)
    x -= game.map_size_x;
  if (y < 0)
    y += game.map_size_y;
  else if (y >= (int)game.map_size_y)
    y -= game.map_size_y;
  while (i < (int)game.map[x][y].player)
    {
      if (i == 0 && x == p->pos_x && y == p->pos_y)
	queue_packet(client, SIMPLE_PACKET, "player");
      else
	queue_packet(client, SIMPLE_PACKET, " player");
      i++;
    }
  print_tiles_next(client, x, y);
}
