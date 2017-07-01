/*
** lifetime.c for lifetime in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:37 2017 Pierre Monge
** Last update Sat Jul  1 03:53:25 2017 Pierre Monge
*/

#include "struct.h"
#include "packet.h"
#include "debug.h"
#include "log.h"
#include "h.h"

void		event_lifetime(void *data)
{
  t_client	*client;
  t_player	*player;

  client = data;
  player = client->data;
  if (player->inventory.food > 0)
    {
      print_log("Player %d from %s: eat food, rest: %d\n", client->net_info.fd,
		player->team->name, player->inventory.food);
      player->inventory.food -= 1;
      queue_chrono(LIFETIME_WITHOUT_FOOD, data, C_EVENT_LIFETIME);
      PRINT_DEBUG("Player %d eat foot\n", client->net_info.fd);
    }
  else
    {
      print_log("Player %d from %s: is dead by anorexy\n",
		client->net_info.fd, player->team->name);
      queue_packet(data, DEAD_PACKET, RPL_DEAD);
      PRINT_DEBUG("Player %d is dead caused by anorexy\n", client->net_info.fd);
    }
}
