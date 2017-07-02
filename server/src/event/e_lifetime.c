/*
** lifetime.c for lifetime in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:37 2017 Pierre Monge
** Last update Sun Jul  2 08:12:57 2017 Pierre Monge
*/

#include "struct.h"
#include "packet.h"
#include "debug.h"
#include "log.h"
#include "h.h"
#include "rfc.h"

int		event_lifetime(void *data)
{
  t_client	*client;
  t_player	*player;

  client = data;
  player = client->data;
  if (player->inventory.food > 0)
    {
      player->inventory.food -= 1;
      print_log("Player %d from %s: eat food, rest: %d\n", client->net_info.fd,
		player->team->name, player->inventory.food);
      queue_chrono(LIFETIME_WITHOUT_FOOD, data, C_EVENT_LIFETIME);
      PRINT_DEBUG("Player %d eat foot\n", client->net_info.fd);
    }
  else
    {
      print_log("Player %d from %s: is dead by anorexy\n",
		client->net_info.fd, player->team->name);
      queue_packet(data, DEAD_PACKET, RPL_DEAD);
      rfc_12(NULL, client);
      PRINT_DEBUG("Player %d is dead caused by anorexy\n", client->net_info.fd);
    }
  return (0);
}
