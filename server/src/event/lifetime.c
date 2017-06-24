/*
** lifetime.c for lifetime in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:37 2017 Pierre Monge
** Last update Fri Jun 23 01:11:44 2017 Pierre Monge
*/

#include "struct.h"
#include "packet.h"
#include "debug.h"
#include "h.h"

void		event_lifetime(void *data)
{
  t_player	*player;

  player = (t_player *)data;
  if (player->inventory.food > 0)
    {
      player->inventory.food -= 1;
      queue_chrono(LIFETIME_WITHOUT_FOOD, data, C_EVENT_LIFETIME);
      PRINT_DEBUG("Player %d eat foot\n", player->net_info.fd);
    }
  else
    {
      queue_packet(player, DEAD_PACKET, RPL_DEAD);
      PRINT_DEBUG("Player %d is dead caused by anorexy\n", player->net_info.fd);
    }
}
