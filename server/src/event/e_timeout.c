/*
** timeout.c for timeout in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:46 2017 Pierre Monge
** Last update Sun Jun 25 01:39:38 2017 Pierre Monge
*/

#include "struct.h"
#include "debug.h"
#include "packet.h"
#include "h.h"

void		event_timeout(void *data)
{
  t_client	*client;

  client = data;
  PRINT_DEBUG("Client %d timeout\n", client->net_info.fd);
  queue_packet(data, DEAD_PACKET, RPL_TIMEOUT);
}
