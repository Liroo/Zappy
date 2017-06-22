/*
** timeout.c for timeout in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:46 2017 Pierre Monge
** Last update Fri Jun 23 00:50:49 2017 Pierre Monge
*/

#include "struct.h"
#include "debug.h"
#include "packet.h"
#include "h.h"

void		event_timeout(void *data)
{
  t_player	*player;

  player = (t_player *)data;
  PRINT_DEBUG("Player %d timeout\n", player->net_info.fd);
  queue_packet(player, DEAD_PACKET, RPL_TIMEOUT);
}
