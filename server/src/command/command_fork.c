/*
** command_fork.c for fork in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 04:13:24 2017 Pierre Monge
** Last update Sat Jul  1 06:29:53 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "h.h"
#include "log.h"
#include "rfc.h"
#include "chrono.h"

int		cmd_fork(t_client *client, char *token)
{
  t_player	*player;
  t_waiting_egg	*waiting_egg;

  (void)token;
  player = client->data;
  if (!(waiting_egg = malloc(sizeof(t_waiting_egg))))
    return (zappy_exit());
  memset(waiting_egg, 0, sizeof(t_waiting_egg));
  waiting_egg->pos_x = player->pos_x;
  waiting_egg->pos_y = player->pos_y;
  waiting_egg->team = player->team;
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  queue_chrono(CHRONO_EGG, waiting_egg, C_EVENT_FORK);
  print_log("Player %d from %s: FORK at %d %d\n", client->net_info.fd,
	    player->team->name, player->pos_x, player->pos_y);
  rfc_15(NULL, client);
  return (0);
}
