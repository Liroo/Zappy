/*
** r_packet.c for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/src
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 15 22:22:38 2017 guicha_t
** Last update Tue Jun 27 02:28:30 2017 Pierre Monge
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "h.h"
#include "fdlist.h"
#include "event.h"
#include "struct.h"
#include "command.h"
#include "packet.h"
#include "debug.h"

static void	process_packet(t_packet packet, t_client *client)
{
  if (packet.block[packet.size] == '\r')
    packet.block[packet.size] = 0;
  if (client->process_r_packet)
    client->process_r_packet(packet, client);
}

/*
** personal implementation of strtok
** used to split packet block with '\n'
** -- optimised to our usage
*/
static void	split_raw_packet(t_packet *s_packet, t_packet *packet)
{
  char		*next_token;

  next_token = memchr(packet->block, '\n', packet->size);
  s_packet->block = packet->block + s_packet->offset;
  if (next_token)
    {
      s_packet->size = next_token - &packet->block[s_packet->offset] - 1;
      s_packet->offset = next_token - packet->block + 1;
      *next_token = 0;
    }
  if (!next_token)
    {
      packet->offset = &packet->block[packet->size]
	- &packet->block[s_packet->offset];
      memmove(packet->block, s_packet->block, s_packet->size);
      s_packet->offset = -1;
    }
}

static int	recv_packet_failed(t_client *client, int recv_ret)
{
  if (recv_ret < 0)
    return (perror("recv"), -1);
  if (recv_ret == 0)
    {
      if (client->client_type == PLAYER &&
	  ((t_player *)(client->data))->command_in_queue == 0
	  && list_empty(&client->w_packet))
	return (-1);
      if (client->client_type == SPECTATOR)
	return (-1);
      if (client->client_type == ADMIN &&
	  ((t_admin *)(client->data))->command_in_queue == 0
	  && list_empty(&client->w_packet))
	return (-1);
      return (-2);
    }
  return (recv_ret);
}

int		recv_packet(t_client *client)
{
  t_packet	s_packet;
  t_packet	*packet;
  int		ret;

  packet = &client->r_packet;
  memset(&s_packet, 0, sizeof(t_packet));
  ret = recv(client->net_info.fd, &packet->block[packet->offset],
	     PACKET_SIZE_DFL - packet->offset, 0);
  if ((ret = recv_packet_failed(client, ret)) < 0)
    return (ret);
  packet->size += ret;
  while (s_packet.offset < packet->size)
    {
      split_raw_packet(&s_packet, packet);
      if (!s_packet.block)
	break;
      if (s_packet.offset == -1)
	return (0);
      else
	process_packet(s_packet, client);
    }
  packet->size = packet->offset = 0;
  memset(packet->block, 0, PACKET_SIZE_DFL);
  return (0);
}
