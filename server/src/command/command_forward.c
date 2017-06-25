/*
** cmds_movement.c for Project-Master in /home/guicha/tek2/Zappy/server/src
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Tue Jun 20 23:05:54 2017 guicha_t
** Last update Sun Jun 25 01:33:02 2017 Pierre Monge
*/

#include "h.h"
#include "debug.h"
#include "game.h"
#include "struct.h"
#include  "chrono.h"
#include "packet.h"

void		pos_about_direction(t_player *p)
{
  if (p->direction == 0)
    {
      p->pos_y++;
      if (p->pos_y >= (int)game.map_size_y)
	p->pos_y = 0;
    }
  else if (p->direction == 1)
    {
      p->pos_x++;
      if (p->pos_x >= (int)game.map_size_x)
	p->pos_x = 0;
    }
  else if (p->direction == 2)
    {
      p->pos_y--;
      if (p->pos_y < 0)
	p->pos_y = game.map_size_y - 1;
    }
  else
    {
      p->pos_x --;
      if (p->pos_x < 0)
	p->pos_x = game.map_size_x - 1;
    }
}

int		cmd_forward(t_client *client, char *token)
{
  t_player	*player;

  player = client->data;
  (void)token;
  --game.map[player->pos_x][player->pos_y].player;
  PRINT_DEBUG("Last pos: [%d][%d]\n", player->pos_x, player->pos_y);
  pos_about_direction(player);
  ++game.map[player->pos_x][player->pos_y].player;
  PRINT_DEBUG("New pos: [%d][%d]\n", player->pos_x, player->pos_y);
  PRINT_DEBUG("Forward ok!\n");
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  player->command_is_running = 1;
  queue_chrono(CHRONO_FORWARD, client, C_EVENT_COMMAND);
  return (0);
}
