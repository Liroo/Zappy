/*
** print_tiles.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Thu Jun 22 05:27:01 2017 Thomas
** Last update Mon Jun 26 00:26:33 2017 Thomas
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
  printf("nbP on x y: %d on %d %d\n", game.map[x][y].player, x, y);
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

void	send_horizontal_look(t_client *client, int range,
			      int begin_direction, int dir_x)
{
  int	begin_y;
  t_player      *p;

  p = client->data;
  begin_y = range * begin_direction;
  printf("H: %d\n", begin_direction);
  if (begin_direction < 0)
    while (begin_y <= range)
      {
	print_tiles(client, p->pos_x + dir_x, p->pos_y + begin_y);
	begin_y++;
	if (begin_y <= range || range == 0)
	  queue_packet(client, SIMPLE_PACKET, ",");
      }
  else if (begin_direction > 0)
    {
      range *= -1;
      while (begin_y >= range)
	{
	  print_tiles(client, p->pos_x + dir_x, p->pos_y + begin_y);
	  begin_y--;
	  if (begin_y >= range || range == 0)
	    queue_packet(client, SIMPLE_PACKET, ",");
	}
    }
}

void	send_vertical_look(t_client *client, int range,
			   int begin_direction, int dir_y)
{
  int	begin_x;
  t_player	*p;

  p = client->data;
  begin_x = range * begin_direction;
  printf("V: %d\n", begin_direction);
  if (begin_direction < 0)
    while (begin_x <= range)
      {
	print_tiles(client, p->pos_x + begin_x, p->pos_y + dir_y);
	begin_x++;
	if (begin_x <= range || range == 0)
	  queue_packet(client, SIMPLE_PACKET, ",");
      }
  else if (begin_direction > 0)
    {
      range *= -1;
      while (begin_x >= range)
	{
	  print_tiles(client, p->pos_x + begin_x, p->pos_y + dir_y);
	  begin_x--;
	  if (begin_x >= range || range == 0)
	    queue_packet(client, SIMPLE_PACKET, ",");
	}
    }
}
