/*
** w_packet.c for w_packet in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 15:17:59 2017 Pierre Monge
** Last update Wed Jun 21 06:04:01 2017 Pierre Monge
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "h.h"
#include "struct.h"
#include "packet.h"
#include "debug.h"
#include "fdlist.h"

void		queue_packet(t_player *player, char dead_packet,
			     char *format, ...)
{
  va_list	va;
  t_packet	*packet;

  if (!(packet = malloc(sizeof(t_packet))))
    {
      PRINT_DEBUG("packet lost for fd: %d\n", player->net_info.fd);
      perror("malloc");
      return ;
    }
  memset(packet, 0, sizeof(t_packet));
  packet->dead_packet = dead_packet;
  va_start(va, format);
  packet->size = vasprintf(&packet->block, format, va);
  va_end(va);
  if (packet->size == -1)
    {
      PRINT_DEBUG("packet lost for fd: %d\n", player->net_info.fd);
      free(packet);
      return ;
    }
  list_add_tail(&packet->list, &player->w_packet);
  fd_set_select(player->net_info.fd, FD_SELECT_READ | FD_SELECT_WRITE, player);
}

int	send_single_packet(int fd, t_packet *packet)
{
  int	w_ret;

  PRINT_DEBUG("sending packet to fd: %d container:\n%s", fd,
	      &packet->block[packet->offset]);
  w_ret = send(fd,
	       &packet->block[packet->offset],
	       packet->size - packet->offset,
	       0);
  if (w_ret < 0)
    {
      perror("send");
      return (w_ret);
    }
  packet->offset = w_ret;
  if (packet->dead_packet == DEAD_PACKET)
    {
      delete_player(fd_entry[fd].data);
      return (-1);
    }
  return (w_ret);
}

void	clear_packet(t_packet *packet)
{
  if (packet->block)
    free(packet->block);
  free(packet);
}

void		send_queued_packet(t_player *player)
{
  t_packet	*container;
  t_list_head	*packet;
  t_list_head	*next;
  int		w_len;

  if (list_empty(&player->w_packet))
    {
      fd_set_select(player->net_info.fd, FD_SELECT_READ, player);
      return ;
    }
  packet = list_get_first(&player->w_packet);
  w_len = 0;
  while (packet != &player->w_packet)
    {
      container = list_entry(packet, t_packet, list);
      if ((w_len = send_single_packet(player->net_info.fd, container)) < 0)
	return ;
      if (w_len < container->size)
	break;
      next = list_del(packet->prev, packet->next);
      clear_packet(container);
      packet = next;
    }
  if (list_empty(&player->w_packet))
    fd_set_select(player->net_info.fd, FD_SELECT_READ, player);
}
