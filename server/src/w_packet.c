/*
** w_packet.c for w_packet in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 15:17:59 2017 Pierre Monge
** Last update Fri Jun 30 19:24:02 2017 Pierre Monge
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "h.h"
#include "struct.h"
#include "packet.h"
#include "debug.h"
#include "fdlist.h"

void		queue_packet(t_client *client, char type,
			     char *format, ...)
{
  va_list	va;
  t_packet	*packet;

  if (!(packet = malloc(sizeof(t_packet))))
    {
      PRINT_DEBUG("packet lost for fd: %d\n", client->net_info.fd);
      perror("malloc");
      return (void)zappy_exit();
    }
  memset(packet, 0, sizeof(t_packet));
  packet->type = type;
  va_start(va, format);
  packet->size = vasprintf(&packet->block, format, va);
  va_end(va);
  if (packet->size == -1)
    {
      PRINT_DEBUG("packet lost for fd: %d\n", client->net_info.fd);
      free(packet);
      return ;
    }
  list_add_tail(&packet->list, &client->w_packet);
  fd_set_select(client->net_info.fd,
		FD_SELECT_READ_P(client, FD_SELECT_WRITE), client);
}

void		queue_packet_va(t_client *client, char type,
				char *format, va_list va)
{
  t_packet	*packet;

  if (!(packet = malloc(sizeof(t_packet))))
    {
      PRINT_DEBUG("packet lost for fd: %d\n", client->net_info.fd);
      perror("malloc");
      return (void)zappy_exit();
    }
  memset(packet, 0, sizeof(t_packet));
  packet->type = type;
  packet->size = vasprintf(&packet->block, format, va);
  if (packet->size == -1)
    {
      PRINT_DEBUG("packet lost for fd: %d\n", client->net_info.fd);
      free(packet);
      return ;
    }
  list_add_tail(&packet->list, &client->w_packet);
  fd_set_select(client->net_info.fd,
		FD_SELECT_READ_P(client, FD_SELECT_WRITE), client);
}

int		send_single_packet(int fd, t_packet *packet)
{
  int		w_ret;
  t_client	*client;

  client = fd_entry[fd].data;
  if (client->client_type == PLAYER)
    PRINT_DEBUG("sending packet to fd: %d container:\n%s", fd,
		&packet->block[packet->offset]);
  w_ret = send(fd,
	       &packet->block[packet->offset],
	       packet->size - packet->offset,
	       MSG_NOSIGNAL);
  if (w_ret < 0)
    {
      perror("send");
      return (w_ret);
    }
  packet->offset = w_ret;
  if (packet->type == DEAD_PACKET)
    return (-1);
  return (w_ret);
}

void	clear_packet(t_packet *packet)
{
  if (packet->block)
    free(packet->block);
  free(packet);
}

int		send_queued_packet(t_client *client)
{
  t_packet	*container;
  t_list_head	*packet;
  t_list_head	*next;
  int		w_len;

  if (list_empty(&client->w_packet))
    {
      fd_set_select(client->net_info.fd, FD_SELECT_READ_P(client, 0), client);
      return (0);
    }
  packet = list_get_first(&client->w_packet);
  w_len = 0;
  while (packet != &client->w_packet)
    {
      container = list_entry(packet, t_packet, list);
      if ((w_len = send_single_packet(client->net_info.fd, container)) < 0)
	return (-1);
      if (w_len < container->size)
	break;
      next = list_del(packet->prev, packet->next);
      clear_packet(container);
      packet = next;
    }
  if (list_empty(&client->w_packet))
    fd_set_select(client->net_info.fd, FD_SELECT_READ_P(client, 0), client);
  return (0);
  // Function more than 26 lines
}
